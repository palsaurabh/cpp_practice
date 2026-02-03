#pragma once

#include <chrono>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

// Timestamped value from a slower-rate stream.
template <typename T>
struct TimedSample {
    TimePoint time;
    T value{};
    bool valid = false;
};
