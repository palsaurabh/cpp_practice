#include <cassert>
#include <cmath>
#include <thread>

#include "controllers.hpp"
#include "multirate_controller.hpp"

int main() {
    const double robot_hz = 100.0;
    const double setpoint_hz = 5.0;
    const double sensor_hz = 20.0;

    auto control_law = [](const double &setpoint, const double &sensor) {
        return proportionalController(setpoint, sensor, 1.0);
    };

    MultiRateController<double, double, double> controller(robot_hz, control_law);

    PeriodicTimer run_timer;
    PeriodicTimer setpoint_timer;
    PeriodicTimer sensor_timer;

    run_timer.start(robot_hz, [&controller]() { controller.run(); });

    setpoint_timer.start(setpoint_hz, [&controller]() {
        static double value = 0.0;
        value = std::sin(value + 0.1);
        controller.updateSetpoint(value);
    });

    sensor_timer.start(sensor_hz, [&controller]() {
        static double value = 0.0;
        value = std::sin(value + 0.05) + 0.1;
        controller.updateSensor(value);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    run_timer.stop();
    setpoint_timer.stop();
    sensor_timer.stop();

    const auto runs = controller.runCount();
    const auto last = controller.lastControl();

    assert(runs > 0);
    assert(last.has_value());
    assert(!std::isnan(*last));
    assert(std::isfinite(*last));

    return 0;
}
