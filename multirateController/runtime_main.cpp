#include <chrono>
#include <iostream>
#include <thread>

#include "runtime_factory.hpp"

int main() {
        // Demo JSON config. Replace with stdin if you want external requests.
        // std::string input((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
        // if (input.empty()) {
        std::string input = R"({
  "controller_config": {
    "robot_rate": 200.0,
    "setpoint_rate": 10.0,
    "sensor_rate": 50.0,
    "setpoint_datatype": "pose",
    "sensor_datatype": "pose"
  }
})";
        // }

    try {
        // Parse config, construct controller, and run the multirate loop.
        const nlohmann::json json = nlohmann::json::parse(input);
        const ControllerConfig config = parseControllerConfig(json);
        auto controller = createController(config);
        controller->start();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        controller->stop();
    } catch (const std::exception &ex) {
        std::cerr << "Failed to create controller: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
