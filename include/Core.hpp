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

inline static int SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& c)
{
    return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

inline static int GetRenderDrawColor(SDL_Renderer* renderer, SDL_Color& c)
{
    return SDL_GetRenderDrawColor(renderer, &c.r, &c.g, &c.b, &c.a);
}

inline static float Degrees(const float& radians)
{
    return radians * (180.0f / M_PIf);
}

inline static float Radians(const float& degrees)
{
    return degrees * (M_PIf / 180.0f);
}

static const SDL_Color COLOR_RED =      { 255, 0,   0,   SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_GREEN =    { 0,   255, 0,   SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_BLUE =     { 0,   0,   255, SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_YELLOW =   { 255, 255, 0,   SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_CYAN =     { 0,   255, 255, SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_MAGENTA =  { 255, 0,   255, SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_WHITE =    { 255, 255, 255, SDL_ALPHA_OPAQUE };
static const SDL_Color COLOR_BLACK =    { 0,   0,   0,   SDL_ALPHA_OPAQUE };

#include "Vector2f.hpp"

#endif // CORE_H