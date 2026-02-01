#pragma once

#include "multirate_controller.hpp"
#include "position_types.hpp"

// Pose interpolator using linear position and quaternion slerp.
struct PoseInterpolator {
    // Interpolate/extrapolate pose between previous and current samples at time t.
    Pose operator()(TimePoint t, const TimedSample<Pose> &prev, const TimedSample<Pose> &curr) const {
        if (!curr.valid) {
            return {};
        }
        if (!prev.valid || curr.time == prev.time) {
            return curr.value;
        }

        const auto dt = std::chrono::duration<double>(curr.time - prev.time).count();
        const auto dt_t = std::chrono::duration<double>(t - prev.time).count();
        const double alpha = dt == 0.0 ? 0.0 : dt_t / dt;
        return interpolate(prev.value, curr.value, alpha);
    }
};
