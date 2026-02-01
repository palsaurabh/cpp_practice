#include <cmath>
#include <iostream>
#include <thread>

#include "controllers.hpp"
#include "interpolators.hpp"
#include "multirate_controller.hpp"
#include "position_types.hpp"

int main() {
    // Robot loop frequency and slower callback frequencies.
    const double robot_hz = 200.0;
    const double setpoint_hz = 10.0;
    const double sensor_hz = 50.0;

    // Common Cartesian controller: position PI + orientation P producing a wrench.
    auto control_law = [](const Pose &setpoint, const Pose &sensor) {
        static Position integral_pos{};
        const double kp_pos = 50.0;
        const double ki_pos = 5.0;
        const double kp_ori = 30.0;
        return cartesianPosePIOrientationP(setpoint, sensor, integral_pos, kp_pos, ki_pos, kp_ori);
    };

    // Publisher to visualize the control flow.
    auto publisher = [](const Wrench &control, const Pose &setpoint, const Pose &sensor) {
        const auto now = Clock::now().time_since_epoch();
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
        std::cout << "t=" << ms << "ms, setpoint_norm=" << norm(setpoint.position)
                  << ", sensor_norm=" << norm(sensor.position)
                  << ", force_norm=" << norm(control.force)
                  << ", torque_norm=" << norm(control.torque) << std::endl;
    };

    // Multirate controller wiring for pose -> wrench with pose interpolation.
    MultiRateController<Pose, Pose, Wrench, PoseInterpolator, PoseInterpolator> controller(
        robot_hz, control_law, {}, {}, publisher);

    PeriodicTimer run_timer;
    PeriodicTimer setpoint_timer;
    PeriodicTimer sensor_timer;

    // Robot-rate loop.
    run_timer.start(robot_hz, [&controller]() { controller.run(); });

    // Lower-rate setpoint stream.
    setpoint_timer.start(setpoint_hz, [&controller]() {
        static double t = 0.0;
        t += 0.1;
        Pose sp;
        sp.position = {std::cos(t), std::sin(t), 0.5 * std::sin(0.5 * t)};
        sp.orientation = normalized({std::cos(0.5 * t), 0.0, 0.0, std::sin(0.5 * t)});
        controller.updateSetpoint(sp);
    });

    // Lower-rate sensor stream.
    sensor_timer.start(sensor_hz, [&controller]() {
        static double t = 0.0;
        t += 0.04;
        Pose s;
        s.position = {std::cos(t) + 0.02, std::sin(t) - 0.01, 0.5 * std::sin(0.5 * t) + 0.01};
        s.orientation = normalized({std::cos(0.5 * t + 0.02), 0.0, 0.0, std::sin(0.5 * t + 0.02)});
        controller.updateSensor(s);
    });

    // Let the demo run briefly.
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Clean shutdown.
    run_timer.stop();
    setpoint_timer.stop();
    sensor_timer.stop();

    return 0;
}
