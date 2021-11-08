#ifndef _FUNCTIONS_H__
#define _FUNCTIONS_H__
#include <algorithm>
#include "../math/Vector.h"
namespace GameEngine
{
    template <typename T>
    T clamp(const T &n, const T &lower, const T &upper)
    {
        return std::max(lower, std::min(n, upper));
    }
    /**
     * Check if a circle with center an radius is on colision with a AABB rectangle. where the rectangle array represents :
     * {MostLeft, MostRight, MostBottom,MostTop}
    */
    bool CheckCicleRectangleCollision(const Vector center, const float radius, const float rectangle[4])
    {

        float closestX = clamp(center.x, rectangle[0], rectangle[1]);
        float closestY = clamp(center.y, rectangle[2], rectangle[3]);

        float distanceX = center.x - closestX;
        float distanceY = center.y - closestY;

        // If the distance is less than the circle's radius, an intersection occurs
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
        return distanceSquared < (radius * radius);
    }
}

#endif