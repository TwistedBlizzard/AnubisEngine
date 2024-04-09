#ifndef CORE_H
#define CORE_H

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

#include "Vector2f.hpp"

#endif // CORE_H