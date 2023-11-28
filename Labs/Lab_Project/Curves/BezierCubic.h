#pragma once

#include <glm/ext.hpp>



class BezierCubic
{
private:
    static const glm::mat4 cubicMatrix;

    glm::mat3x4 pointMatrix;

public:
    BezierCubic();
    BezierCubic(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);

    glm::vec3 getPoint(float t);
};