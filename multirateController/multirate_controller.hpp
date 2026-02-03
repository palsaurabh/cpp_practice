#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <optional>
#include <mutex>
#include <thread>

#include "interpolators.hpp"
#include "multirate_types.hpp"

class PeriodicTimer {
public:
    PeriodicTimer() = default;

    ~PeriodicTimer() {
        stop();
    }

    // Start periodic callback execution at the requested frequency.
    void start(double frequency_hz, std::function<void()> callback) {
        stop();
        running_.store(true);
        thread_ = std::thread([this, frequency_hz, callback = std::move(callback)]() {
            using namespace std::chrono;
            const auto period = duration<double>(1.0 / frequency_hz);
            auto next = Clock::now() + period;
            while (running_.load()) {
                callback();
                std::this_thread::sleep_until(next);
                next += period;
            }
        });
    }

    // Stop the timer and join the worker thread.
    void stop() {
        running_.store(false);
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    std::atomic<bool> running_{false};
    std::thread thread_;
};

// Generic multirate controller.
// - SetpointT: setpoint stream type
// - SensorT: sensor stream type
// - ControlT: control output type
// - Interpolators: map lower-rate streams to robot-rate samples
template <typename SetpointT,
          typename SensorT,
          typename ControlT,
          typename SetpointInterpolator = LinearInterpolator<SetpointT>,
          typename SensorInterpolator = LinearInterpolator<SensorT>>
class MultiRateController {
public:
    // Control law to generate the control output from setpoint and sensor samples.
    using ControlLaw = std::function<ControlT(const SetpointT &, const SensorT &)>;
    // Publisher for side effects (logging, transport, etc.).
    using Publisher = std::function<void(const ControlT &, const SetpointT &, const SensorT &)>;

    // Create a controller that runs at the robot frequency.
    MultiRateController(double robot_frequency_hz,
                        ControlLaw control_law,
                        SetpointInterpolator setpoint_interpolator = {},
                        SensorInterpolator sensor_interpolator = {},
                        Publisher publisher = nullptr)
        : robot_frequency_hz_(robot_frequency_hz),
          control_law_(std::move(control_law)),
          setpoint_interpolator_(std::move(setpoint_interpolator)),
          sensor_interpolator_(std::move(sensor_interpolator)),
          publisher_(std::move(publisher)) {}

    // Callback to push a new setpoint sample (lower-rate stream).
    void updateSetpoint(const SetpointT &value) {
        const auto now = Clock::now();
        std::lock_guard<std::mutex> lock(setpoint_mutex_);
        setpoint_prev_ = setpoint_curr_;
        setpoint_curr_ = {now, value, true};
    }

    // Callback to push a new sensor sample (lower-rate stream).
    void updateSensor(const SensorT &value) {
        const auto now = Clock::now();
        std::lock_guard<std::mutex> lock(sensor_mutex_);
        sensor_prev_ = sensor_curr_;
        sensor_curr_ = {now, value, true};
    }

    // Robot-rate callback: sample inputs, compute control, and publish.
    void run() {
        const auto now = Clock::now();
        const SetpointT setpoint = sampleAt(now, setpoint_prev_, setpoint_curr_, setpoint_mutex_, setpoint_interpolator_);
        const SensorT sensor = sampleAt(now, sensor_prev_, sensor_curr_, sensor_mutex_, sensor_interpolator_);
        if (!control_law_) {
            return;
        }
        const ControlT control = control_law_(setpoint, sensor);
        if (publisher_) {
            publisher_(control, setpoint, sensor);
        }
        {
            std::lock_guard<std::mutex> lock(control_mutex_);
            last_control_ = control;
            last_control_valid_ = true;
        }
        run_count_.fetch_add(1);
    }

    // Latest computed control value from the last run.
    std::optional<ControlT> lastControl() const {
        std::lock_guard<std::mutex> lock(control_mutex_);
        if (!last_control_valid_) {
            return std::nullopt;
        }
        return last_control_;
    }

    // Number of times run() has executed.
    std::uint64_t runCount() const {
        return run_count_.load();
    }

private:
    // Interpolate/extrapolate between the last two samples to time t.
    template <typename T, typename Interpolator>
    T sampleAt(TimePoint t,
               const TimedSample<T> &prev,
               const TimedSample<T> &curr,
               std::mutex &mtx,
               const Interpolator &interpolator) {
        std::lock_guard<std::mutex> lock(mtx);
        return interpolator(t, prev, curr);
    }

    double robot_frequency_hz_ = 0.0;
    ControlLaw control_law_;
    SetpointInterpolator setpoint_interpolator_{};
    SensorInterpolator sensor_interpolator_{};
    Publisher publisher_;

    TimedSample<SetpointT> setpoint_prev_{};
    TimedSample<SetpointT> setpoint_curr_{};
    TimedSample<SensorT> sensor_prev_{};
    TimedSample<SensorT> sensor_curr_{};

    std::mutex setpoint_mutex_;
    std::mutex sensor_mutex_;

    mutable std::mutex control_mutex_;
    ControlT last_control_{};
    bool last_control_valid_ = false;
    std::atomic<std::uint64_t> run_count_{0};
};
