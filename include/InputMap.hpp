#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "Core.hpp"

#include <fstream>
using std::ifstream;

enum InputMethod
{
    KEYBOARD,
    MOUSE_BUTTON,
    GAMEPAD_BUTTON,
    MOUSE_POSITION,
    MOUSE_RELATIVE,
    GAMEPAD_LEFT_STICK,
    GAMEPAD_RIGHT_STICK,
    GAMEPAD_LEFT_TRIGGER,
    GAMEPAD_RIGHT_TRIGGER
};

const map<string, InputMethod> MethodLookup
{
    {"Keyboard",        KEYBOARD},
    {"MouseButton",     MOUSE_BUTTON},
    {"GamepadButton",   GAMEPAD_BUTTON},
    {"MousePos",        MOUSE_POSITION},
    {"MouseRel",        MOUSE_RELATIVE},
    {"LeftStick",       GAMEPAD_LEFT_STICK},
    {"RightStick",      GAMEPAD_RIGHT_STICK},
    {"LeftTrigger",     GAMEPAD_LEFT_TRIGGER},
    {"RightTrigger",    GAMEPAD_RIGHT_TRIGGER}
};

const map<string, int> MouseButtonLookup
{
    {"Left",    SDL_BUTTON_LEFT},
    {"Right",   SDL_BUTTON_RIGHT},
    {"Middle",  SDL_BUTTON_MIDDLE},
    {"X1",      SDL_BUTTON_X1},
    {"X2",      SDL_BUTTON_X2}
};

#endif // INPUTMAP_H