#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2f.hpp"

struct Transform
{
    Vector2f position {0.0f, 0.0f};
    double rotation = 0.0;
};

#endif // TRANSFORM_H