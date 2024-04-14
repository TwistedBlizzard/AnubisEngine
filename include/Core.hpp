#ifndef CORE_H
#define CORE_H

#include <cmath>

#ifndef M_PIf
#define M_PIf 3.14159265358979323846f
#endif // M_PIf

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <unordered_map>
template <class _key, class _value>
using map = std::unordered_map<_key, _value>;

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

inline static float Degrees(const float& radians)
{
    return radians * (180.0f / M_PIf);
}

inline static float Radians(const float& degrees)
{
    return degrees * (M_PIf / 180.0f);
}

#include "Vector2f.hpp"

#endif // CORE_H