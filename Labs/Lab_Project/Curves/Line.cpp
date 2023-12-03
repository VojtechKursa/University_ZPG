#include "Line.h"



Line::Line(glm::vec3 originPoint, glm::vec3 value2, bool value2IsPoint)
    : originPoint(originPoint), directionalVector(value2IsPoint ? value2 - originPoint : value2)
{ }



glm::vec3 Line::getPoint(float t)
{
    return this->originPoint + this->directionalVector * t;
}
