#pragma once

#include <cmath>

// 3D Cartesian position.
struct Position {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

// Unit quaternion for 3D orientation (w + xi + yj + zk).
struct Quaternion {
    double w = 1.0;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

// Pose = position + orientation.
struct Pose {
    Position position{};
    Quaternion orientation{};
};

// Wrench = force + torque.
struct Wrench {
    Position force{};
    Position torque{};
};

// Position addition.
inline Position operator+(const Position &a, const Position &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

// Position subtraction.
inline Position operator-(const Position &a, const Position &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// Position scaling by a scalar.
inline Position operator*(const Position &a, double scalar) {
    return {a.x * scalar, a.y * scalar, a.z * scalar};
}

// Position division by a scalar.
inline Position operator/(const Position &a, double scalar) {
    return {a.x / scalar, a.y / scalar, a.z / scalar};
}

// Euclidean norm of a position vector.
inline double norm(const Position &p) {
    return std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

// Quaternion dot product.
inline double dot(const Quaternion &a, const Quaternion &b) {
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

// Quaternion addition.
inline Quaternion operator+(const Quaternion &a, const Quaternion &b) {
    return {a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z};
}

// Quaternion subtraction.
inline Quaternion operator-(const Quaternion &a, const Quaternion &b) {
    return {a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z};
}

// Quaternion scaling by a scalar.
inline Quaternion operator*(const Quaternion &q, double scalar) {
    return {q.w * scalar, q.x * scalar, q.y * scalar, q.z * scalar};
}

// Quaternion division by a scalar.
inline Quaternion operator/(const Quaternion &q, double scalar) {
    return {q.w / scalar, q.x / scalar, q.y / scalar, q.z / scalar};
}

// Normalize quaternion; returns identity if input is zero.
inline Quaternion normalized(const Quaternion &q) {
    const double n = std::sqrt(dot(q, q));
    if (n == 0.0) {
        return {1.0, 0.0, 0.0, 0.0};
    }
    return q / n;
}

// Quaternion conjugate (inverse for unit quaternion).
inline Quaternion conjugate(const Quaternion &q) {
    return {q.w, -q.x, -q.y, -q.z};
}

// Quaternion multiplication (composition of rotations).
inline Quaternion multiply(const Quaternion &a, const Quaternion &b) {
    return {
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
    };
}

// Spherical linear interpolation between two orientations.
inline Quaternion slerp(const Quaternion &from, const Quaternion &to, double t) {
    Quaternion q1 = normalized(from);
    Quaternion q2 = normalized(to);
    double cos_theta = dot(q1, q2);

    if (cos_theta < 0.0) {
        q2 = q2 * -1.0;
        cos_theta = -cos_theta;
    }

    constexpr double kEps = 1e-6;
    if (1.0 - cos_theta < kEps) {
        return normalized(q1 + (q2 - q1) * t);
    }

    const double theta = std::acos(cos_theta);
    const double sin_theta = std::sin(theta);
    const double w1 = std::sin((1.0 - t) * theta) / sin_theta;
    const double w2 = std::sin(t * theta) / sin_theta;
    return normalized(q1 * w1 + q2 * w2);
}

// Interpolate pose with linear position and quaternion slerp.
inline Pose interpolate(const Pose &a, const Pose &b, double alpha) {
    return {
        a.position + (b.position - a.position) * alpha,
        slerp(a.orientation, b.orientation, alpha)
    };
}
