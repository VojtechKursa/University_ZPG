#pragma once

class Rotation
{
public:
    float yaw;      // yaw angle, in radians
    float pitch;    // pitch angle, in radians
    float roll;     // roll angle, in radians

    Rotation();
    Rotation(float yaw, float pitch, float roll);

    friend Rotation operator+(const Rotation& left, const Rotation& right);
    friend Rotation operator-(const Rotation& left, const Rotation& right);
    friend Rotation operator*(const float left, const Rotation& right);
};