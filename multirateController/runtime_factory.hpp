#pragma once

#include <chrono>
#include <cmath>
#include <cctype>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "controllers.hpp"
#include "interpolators.hpp"
#include "multirate_controller.hpp"
#include "position_types.hpp"
#include "third_party/nlohmann/json.hpp"

// Supported runtime data types for setpoint/sensor streams.
enum class DataType {
    kScalar,
    kPosition,
    kPose
};

// Parsed controller configuration from JSON.
struct ControllerConfig {
    double robot_rate_hz = 0.0;
    double setpoint_rate_hz = 0.0;
    double sensor_rate_hz = 0.0;
    DataType setpoint_type = DataType::kScalar;
    DataType sensor_type = DataType::kScalar;
};

// Lowercase helper for parsing user-provided strings.
inline std::string toLower(std::string value) {
    for (char &ch : value) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return value;
}

// Convert a datatype string into the runtime enum.
inline DataType parseDataType(const std::string &value) {
    const std::string lowered = toLower(value);
    if (lowered == "scalar" || lowered == "double" || lowered == "float") {
        return DataType::kScalar;
    }
    if (lowered == "position" || lowered == "vector3") {
        return DataType::kPosition;
    }
    if (lowered == "pose" || lowered == "pose3" || lowered == "se3") {
        return DataType::kPose;
    }
    throw std::runtime_error("Unsupported data type: " + value);
}

// Parse controller configuration from JSON.
// Accepts either {"controller_config": {...}} or a config object directly.
inline ControllerConfig parseControllerConfig(const nlohmann::json &json) {
    const nlohmann::json &cfg = json.contains("controller_config") ? json.at("controller_config") : json;

    ControllerConfig config;
    config.robot_rate_hz = cfg.at("robot_rate").get<double>();
    config.setpoint_rate_hz = cfg.at("setpoint_rate").get<double>();
    config.sensor_rate_hz = cfg.at("sensor_rate").get<double>();
    config.setpoint_type = parseDataType(cfg.at("setpoint_datatype").get<std::string>());
    config.sensor_type = parseDataType(cfg.at("sensor_datatype").get<std::string>());
    return config;
}

// Interface for runtime-managed controllers created by the factory.
class IRuntimeController {
public:
    virtual ~IRuntimeController() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

template <typename SetpointT,
          typename SensorT,
          typename ControlT,
          typename SetpointInterpolator,
          typename SensorInterpolator>
class RuntimeController final : public IRuntimeController {
public:
    // Generator for synthetic setpoint stream values.
    using SetpointGenerator = std::function<SetpointT()>;
    // Generator for synthetic sensor stream values.
    using SensorGenerator = std::function<SensorT()>;
    // Control law used at robot rate.
    using ControlLaw = typename MultiRateController<SetpointT, SensorT, ControlT,
                                                    SetpointInterpolator,
                                                    SensorInterpolator>::ControlLaw;
    // Optional publisher to log or publish control data.
    using Publisher = typename MultiRateController<SetpointT, SensorT, ControlT,
                                                   SetpointInterpolator,
                                                   SensorInterpolator>::Publisher;

    RuntimeController(const ControllerConfig &config,
                      SetpointGenerator setpoint_generator,
                      SensorGenerator sensor_generator,
                      ControlLaw control_law,
                      SetpointInterpolator setpoint_interpolator = {},
                      SensorInterpolator sensor_interpolator = {},
                      Publisher publisher = nullptr)
        : config_(config),
          controller_(config.robot_rate_hz,
                      std::move(control_law),
                      std::move(setpoint_interpolator),
                      std::move(sensor_interpolator),
                      std::move(publisher)),
          setpoint_generator_(std::move(setpoint_generator)),
          sensor_generator_(std::move(sensor_generator)) {}

    // Start timers for run, setpoint, and sensor updates.
    void start() override {
        run_timer_.start(config_.robot_rate_hz, [this]() { controller_.run(); });
        setpoint_timer_.start(config_.setpoint_rate_hz, [this]() {
            controller_.updateSetpoint(setpoint_generator_());
        });
        sensor_timer_.start(config_.sensor_rate_hz, [this]() {
            controller_.updateSensor(sensor_generator_());
        });
    }

    // Stop all timers.
    void stop() override {
        run_timer_.stop();
        setpoint_timer_.stop();
        sensor_timer_.stop();
    }

private:
    ControllerConfig config_;
    MultiRateController<SetpointT, SensorT, ControlT, SetpointInterpolator, SensorInterpolator> controller_;
    PeriodicTimer run_timer_;
    PeriodicTimer setpoint_timer_;
    PeriodicTimer sensor_timer_;
    SetpointGenerator setpoint_generator_;
    SensorGenerator sensor_generator_;
};

// Factory that builds a runtime controller based on the requested data type.
// For this demo, setpoint and sensor types must match.
inline std::unique_ptr<IRuntimeController> createController(const ControllerConfig &config) {
    if (config.setpoint_type != config.sensor_type) {
        throw std::runtime_error("Setpoint and sensor types must match for this demo");
    }

    if (config.setpoint_type == DataType::kScalar) {
        // Scalar control: proportional controller.
        auto control_law = [](const double &setpoint, const double &sensor) {
            return proportionalController(setpoint, sensor, 1.0);
        };

        // Scalar logger.
        auto publisher = [](const double &control, const double &setpoint, const double &sensor) {
            const auto now = Clock::now().time_since_epoch();
            const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
            std::cout << "t=" << ms << "ms, setpoint=" << setpoint
                      << ", sensor=" << sensor << ", control=" << control << std::endl;
        };

        // Synthetic scalar streams.
        auto setpoint_gen = []() {
            static double t = 0.0;
            t += 0.1;
            return std::sin(t);
        };

        auto sensor_gen = []() {
            static double t = 0.0;
            t += 0.05;
            return std::sin(t) + 0.1;
        };

        return std::make_unique<RuntimeController<double, double, double,
                                                   LinearInterpolator<double>,
                                                   LinearInterpolator<double>>>(
            config,
            setpoint_gen,
            sensor_gen,
            control_law,
            LinearInterpolator<double>{},
            LinearInterpolator<double>{},
            publisher);
    }

    if (config.setpoint_type == DataType::kPosition) {
        // Position control: proportional on Cartesian error.
        auto control_law = [](const Position &setpoint, const Position &sensor) {
            return proportionalPositionController(setpoint, sensor, 10.0);
        };

        // Position logger.
        auto publisher = [](const Position &control, const Position &setpoint, const Position &sensor) {
            const auto now = Clock::now().time_since_epoch();
            const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
            std::cout << "t=" << ms << "ms, setpoint_norm=" << norm(setpoint)
                      << ", sensor_norm=" << norm(sensor)
                      << ", control_norm=" << norm(control) << std::endl;
        };

        // Synthetic position streams.
        auto setpoint_gen = []() {
            static double t = 0.0;
            t += 0.1;
            return Position{std::cos(t), std::sin(t), 0.5 * std::sin(0.5 * t)};
        };

        auto sensor_gen = []() {
            static double t = 0.0;
            t += 0.05;
            return Position{std::cos(t) + 0.02, std::sin(t) - 0.01, 0.5 * std::sin(0.5 * t) + 0.01};
        };

        return std::make_unique<RuntimeController<Position, Position, Position,
                                                   LinearInterpolator<Position>,
                                                   LinearInterpolator<Position>>>(
            config,
            setpoint_gen,
            sensor_gen,
            control_law,
            LinearInterpolator<Position>{},
            LinearInterpolator<Position>{},
            publisher);
    }

    if (config.setpoint_type == DataType::kPose) {
        auto integral_pos = std::make_shared<Position>();
        // Pose control: position PI + orientation P, output wrench.
        auto control_law = [integral_pos](const Pose &setpoint, const Pose &sensor) {
            const double kp_pos = 50.0;
            const double ki_pos = 5.0;
            const double kp_ori = 30.0;
            return cartesianPosePIOrientationP(setpoint, sensor, *integral_pos, kp_pos, ki_pos, kp_ori);
        };

        // Pose logger.
        auto publisher = [](const Wrench &control, const Pose &setpoint, const Pose &sensor) {
            const auto now = Clock::now().time_since_epoch();
            const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
            std::cout << "t=" << ms << "ms, setpoint_norm=" << norm(setpoint.position)
                      << ", sensor_norm=" << norm(sensor.position)
                      << ", force_norm=" << norm(control.force)
                      << ", torque_norm=" << norm(control.torque) << std::endl;
        };

        // Synthetic pose streams.
        auto setpoint_gen = []() {
            static double t = 0.0;
            t += 0.1;
            Pose sp;
            sp.position = {std::cos(t), std::sin(t), 0.5 * std::sin(0.5 * t)};
            sp.orientation = normalized({std::cos(0.5 * t), 0.0, 0.0, std::sin(0.5 * t)});
            return sp;
        };

        auto sensor_gen = []() {
            static double t = 0.0;
            t += 0.04;
            Pose s;
            s.position = {std::cos(t) + 0.02, std::sin(t) - 0.01, 0.5 * std::sin(0.5 * t) + 0.01};
            s.orientation = normalized({std::cos(0.5 * t + 0.02), 0.0, 0.0, std::sin(0.5 * t + 0.02)});
            return s;
        };

        return std::make_unique<RuntimeController<Pose, Pose, Wrench,
                                                   PoseInterpolator,
                                                   PoseInterpolator>>(
            config,
            setpoint_gen,
            sensor_gen,
            control_law,
            PoseInterpolator{},
            PoseInterpolator{},
            publisher);
    }

    throw std::runtime_error("Unsupported configuration");
}
