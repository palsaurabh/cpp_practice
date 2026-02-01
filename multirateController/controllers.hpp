#pragma once

#include "position_types.hpp"

// Simple proportional controller for scalar signals.
inline double proportionalController(double setpoint, double sensor, double kp) {
    return kp * (setpoint - sensor);
}

// Cartesian position PI + orientation P controller producing a wrench.
inline Wrench cartesianPosePIOrientationP(const Pose &setpoint,
                                         const Pose &sensor,
                                         Position &integral_pos,
                                         double kp_pos,
                                         double ki_pos,
                                         double kp_ori) {
    const Position pos_error = setpoint.position - sensor.position;
    integral_pos = integral_pos + pos_error * ki_pos;

    const Quaternion q_err = multiply(setpoint.orientation, conjugate(sensor.orientation));
    const Position ori_error{q_err.x, q_err.y, q_err.z};

    Wrench wrench;
    wrench.force = pos_error * kp_pos + integral_pos;
    wrench.torque = ori_error * kp_ori;
    return wrench;
}
