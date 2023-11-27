#include "BezierCubic.h"



const glm::mat4 BezierCubic::thingMatrix = glm::mat4
(
    glm::vec4(-1.0, 	3.0, 	-3.0, 	1.0),
    glm::vec4(3.0, 		-6.0, 	3.0, 	0),
    glm::vec4(-3.0, 	3.0, 	0, 		0),
    glm::vec4(1, 		0, 		0, 		0)
);



BezierCubic::BezierCubic()
{ }

BezierCubic::BezierCubic(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
{
    pointMatrix = glm::transpose(glm::mat4x3(p1, p2, p3, p4));
}



glm::vec3 BezierCubic::getPoint(float t)
{
    glm::vec4 parameters = glm::vec4(t*t*t, t*t, t, 1.f);

    return parameters * BezierCubic::thingMatrix * this->pointMatrix;
}
