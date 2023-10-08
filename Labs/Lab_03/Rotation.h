#pragma once

class Rotation
{
public:
    float yaw;      // yaw angle, in radians
    float pitch;    // pitch angle, in radians
    float roll;     // roll angle, in radians

    Rotation();
    Rotation(float angle);
    Rotation(float yaw, float pitch, float roll);

    friend Rotation operator+(const Rotation& left, const Rotation& right);
    friend Rotation operator-(const Rotation& left, const Rotation& right);
    friend Rotation operator*(const float left, const Rotation& right);
    inline friend Rotation operator*(const Rotation& left, const float right) { return right * left; }
};