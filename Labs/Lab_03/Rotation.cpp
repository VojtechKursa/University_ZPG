#include "Rotation.h"

Rotation::Rotation()
    : Rotation(0,0,0)
{ }

Rotation::Rotation(float yaw, float pitch, float roll)
{
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
}

Rotation operator+(const Rotation &left, const Rotation &right)
{
    return Rotation(left.yaw + right.yaw, left.pitch + right.pitch, left.roll + right.roll);
}

Rotation operator-(const Rotation &left, const Rotation &right)
{
    return Rotation(left.yaw - right.yaw, left.pitch - right.pitch, left.roll - right.roll);
}

Rotation operator*(const float left, const Rotation &right)
{
    return Rotation(left * right.yaw, left * right.pitch, left * right.roll);
}
