#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Core.hpp"

struct Transform
{
    Vector2f position {0.0f, 0.0f};
    double rotation = 0.0;

    Transform operator+(const Transform& rhs)
    {
        return Transform
        {
            position + rhs.position,
            rotation + rhs.rotation
        };
    }

    Transform operator-(const Transform& rhs)
    {
        return Transform
        {
            position - rhs.position,
            rotation - rhs.rotation
        };
    }

    Transform operator+=(const Transform& rhs)
    {
        return Transform
        {
            position += rhs.position,
            rotation += rhs.rotation
        };
    }

    Transform operator-=(const Transform& rhs)
    {
        return Transform
        {
            position -= rhs.position,
            rotation -= rhs.rotation
        };
    }
};

#endif // TRANSFORM_H