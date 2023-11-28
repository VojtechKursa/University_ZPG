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

    

    // first cubic
    cubics.push_back(BezierCubic(points[0], points[1], points[2], points[3]));

    
    
    glm::vec3 cubicPoints[4] = {points[0], points[1], points[2], points[3]};

    int lastCubicPointsIndex = 0;

    for(size_t i = 4; i < points.size(); i++)
    {
        cubicPoints[lastCubicPointsIndex++] = points[i];

        if(lastCubicPointsIndex == 3)
        {
            cubics.push_back(BezierCubic(cubicPoints[3], cubicPoints[0], cubicPoints[1], cubicPoints[2]));

            cubicPoints[3] = cubicPoints[2];
            lastCubicPointsIndex = 0;
        }
    }
}



glm::vec3 BezierCurve::getPoint(float t)
{
    t = t * this->cubics.size();

    int selectedCubic = static_cast<int>(floor(t));
    if (selectedCubic >= this->cubics.size())
        selectedCubic = this->cubics.size() - 1;
    else if (selectedCubic < 0)
        selectedCubic = 0;

    t = t - selectedCubic;

    return this->cubics[selectedCubic].getPoint(t);
}



size_t BezierCurve::getCubicsCount()
{
    return this->cubics.size();
}
