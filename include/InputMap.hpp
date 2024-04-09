#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "Core.hpp"

#include <fstream>
using std::ifstream;

enum InputType
{
    AXIS,       // Range: -1.0f to 1.0f
    BOOL,       // Range: true or false
    SCALAR      // Range: 0.0f to 1.0f
};

enum InputMethod
{
    KEYBOARD,
    MOUSE_AXIS,
    MOUSE_BUTTON,
    GAMEPAD_AXIS,
    GAMEPAD_BUTTON
};

enum MouseAxis
{
    X,
    Y
};

const map<string, InputType> TypeLookup
{
    {"AXIS",    AXIS},
    {"BOOL",    BOOL},
    {"SCALAR",  SCALAR}
};

const map<string, InputMethod> MethodLookup
{
    {"Keyboard",        KEYBOARD},
    {"MouseAxis",       MOUSE_AXIS},
    {"MouseButton",     MOUSE_BUTTON},
    {"GamepadAxis",     GAMEPAD_AXIS},
    {"GamepadButton",   GAMEPAD_BUTTON}
};

const map<string, MouseAxis> MouseAxisLookup
{
    {"X",   X},
    {"Y",   Y}
};

const map<string, int> MouseButtonLookup
{
    {"Left",    SDL_BUTTON_LEFT},
    {"Right",   SDL_BUTTON_RIGHT},
    {"Middle",  SDL_BUTTON_MIDDLE},
    {"X1",      SDL_BUTTON_X1},
    {"X2",      SDL_BUTTON_X2}
};

const map<string, bool> InvertLookup
{
    {"NOR",     false},
    {"INV",     true}
};

const map<string, int> SignLookup
{
    {"POS",     1},     // Set value to 1.0 if true
    {"NEG",     -1}     // Set value to -1.0 if true
};

struct InputAction
{
    bool Invert;
    float Multiplier;
    string Destination;
};

// This is ugly but the alternatives are worse
typedef map<InputMethod, map<Sint32, InputAction>> InputMap;
typedef map<string, InputType> ActionMap;

bool ParseInputMap(InputMap& inputMap, ActionMap& actionMap);
bool GetInput(string inputString, InputType inputType, InputMethod inputMethod, Sint32& input);
bool GetAxisInput(string inputString, InputMethod inputMethod, Sint32& input);
bool GetBoolInput(string inputString, InputMethod inputMethod, Sint32& input);
bool GetScalarInput(string inputString, InputMethod inputMethod, Sint32& input);
bool GetSign(InputAction& InputAction, string signString);

#endif // INPUTMAP_H