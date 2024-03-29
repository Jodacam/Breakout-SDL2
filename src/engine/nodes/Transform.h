#pragma once
#include "../math/Vector.h"
namespace LightCanvas {
    class Transform
    {
    private:
        /* data */
        Vector position;
        float rotation;
        Vector scale = Vector(1,1);
    public:
        Transform(/* args */);
        ~Transform();
        inline const Vector& GetPosition() const { return position; };
        inline const Vector& GetScale() const { return scale; };
        inline float GetRotation() const { return rotation; };
        inline void SetPosition(const Vector pos) { position = pos; };
        inline void SetScale(const Vector scl) { scale = scl; };
        inline void SetRotation(float r) { rotation = r; };
    };

}

