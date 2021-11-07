#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>
#include <iostream>
namespace GameEngine
{

    /**
     * Common struct to store a 2D vector.
    */
    struct Vector
    {
        float x = 0.0f;
        float y = 0.0f;
        Vector(const Vector &a)
        {
            x = a.x;
            y = a.y;
        }
        Vector(float x, float y) : x(x), y(y)
        {
        }
        Vector()
        {
            x = 0.0f;
            y = 0.0f;
        }
        Vector operator+(const Vector a)
        {
            return Vector(a.x + x, a.y + y);
        }
        Vector operator-(const Vector a)
        {
            return Vector(x - a.x, y - a.y);
        }
        Vector operator*(const float m)
        {
            return Vector(m * x, m * y);
        }
        Vector operator/(const float m)
        {
            return Vector(x / m, y / m);
        }
        Vector Rotate(float angle) {
            return Vector::Rotate(angle,*this);
        }
        inline Vector Normalized()
        {
            float module = Module();
            return Vector(x / module, y / module);
        }

        //TODO optimize module cache. sqrt is a expensive operation
        inline float Module() { return sqrt(x * x + y * y); }
        /**
         * Return the non square root of the module. Basically is x^2+y^2. This is useful when you want to check distances. When you're checking if the point a is closer to another point than point b
         * you can compare the non square root modules because sqrt(x) < sqrt(y) <===> x < y
        */
        inline float sqrtModule() { return x * x + y * y; }

        //Static functions

        /**
         * Return the distances between two point. Is the module of _b-_a
        */
        static float Distance(Vector _a, Vector _b) { return (_b - _a).Module(); }

        static float DotProduct(const Vector _a, const Vector _b)
        {
            return _a.x * _b.x + _a.y * _b.y;
        }

        static Vector Rotate(float angle, Vector _a) { 

            auto cs = std::cos(angle);
            auto sn = std::sin(angle);

            float nX = _a.x*cs-_a.y*sn;
            float nY = _a.x*sn+_a.y*cs;
            return Vector(nX, nY);
        }

        static float Angle(Vector _a, Vector _b) { return acos(Vector::DotProduct(_a, _b) / (_a.Module() * _b.Module())); }

        friend std::ostream &operator<<(std::ostream &os, const Vector &v)
        {
            os<< "Vector with x("<< v.x << ")" << " y("<<v.y<<") ";
            return os;
        }
    };

}
#endif