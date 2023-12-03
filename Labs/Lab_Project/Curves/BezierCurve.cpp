#include "BezierCurve.h"

#include <queue>



BezierCurve::BezierCurve()
{
    cubics.push_back(BezierCubic(
        glm::vec3(-1, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(1, 0, 0)
    ));
}

BezierCurve::BezierCurve(std::vector<glm::vec3> points)
{
    if (points.size() < 4)
    {
        throw "Invalid curve";
        return;
    }

    
    
    glm::vec3 cubicPoints[4] { };

    int lastCubicPointsIndex = 0;

    for(size_t i = 0; i < points.size(); i++)
    {
        cubicPoints[lastCubicPointsIndex++] = points[i];

        if(lastCubicPointsIndex == 4)
        {
            cubics.push_back(BezierCubic(cubicPoints[0], cubicPoints[1], cubicPoints[2], cubicPoints[3]));

            cubicPoints[0] = cubicPoints[3];
            lastCubicPointsIndex = 1;
        }
    }
}



glm::vec3 BezierCurve::getPoint(float t)
{
    t = t * this->cubics.size();

    size_t selectedCubic = static_cast<size_t>(floor(t));
    if (selectedCubic >= this->cubics.size())
        selectedCubic = this->cubics.size() - 1;
    else if (selectedCubic < 0)
        selectedCubic = 0;

    t = t - selectedCubic;

    return this->cubics[selectedCubic].getPoint(t);
}



size_t BezierCurve::getSegmentCount()
{
    return this->cubics.size();
}
