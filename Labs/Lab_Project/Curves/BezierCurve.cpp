#include "BezierCurve.h"

#include <queue>



BezierCurve::BezierCurve(std::vector<glm::vec3> points)
{
    if(points.size() < 4)
        throw "Invalid curve";

    

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

    if(lastCubicPointsIndex == 0)
    {
        lastOffset = 0;
    }
    else
    {
        cubics.push_back(BezierCubic(
            cubicPoints[lastCubicPointsIndex],
            cubicPoints[lastCubicPointsIndex + 1 % 4],
            cubicPoints[lastCubicPointsIndex + 2 % 4],
            cubicPoints[lastCubicPointsIndex + 3 % 4]
        ));

        lastOffset = 4 - lastCubicPointsIndex;
    }
}



glm::vec3 BezierCurve::getPoint(float t)
{
    
}
