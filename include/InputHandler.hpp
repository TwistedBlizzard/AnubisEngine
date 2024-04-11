#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <map>

#include "Core.hpp"

#include "InputMap.hpp"

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void HandleEvent(const SDL_Event& event);

    bool RegisterValue(InputMethod method, string input, bool* value);
    bool RegisterValue(InputMethod method, Vector2f* value);
    bool RegisterValue(InputMethod method, float* value);

    void UnregisterValue(InputMethod method);
    void UnregisterValue(InputMethod method, string input);

private:
    bool m_initialised;

    map<SDL_Keycode, bool*> m_keys;
    map<int, bool*> m_mouseButtons;
    map<Uint8, bool*> m_gamepadButtons;

    Vector2f* m_mousePos;
    Vector2f* m_mouseRel;
    Vector2f* m_leftStick;
    Vector2f* m_rightStick;

    float* m_leftTrigger;
    float* m_rightTrigger;

    bool m_invertLeftX;
    bool m_invertLeftY;
    bool m_invertRightX;
    bool m_invertRightY;

    ifstream m_stream;
    int m_line;

    void HandleKeyboard(SDL_Keycode key, bool value);
    void HandleMouseButton(int button, bool value);
    void HandleGamepadButton(Uint8 button, bool value);
    void HandleMouseMotion(float x, float y, float xrel, float yrel);
    void HandleGamepadAxis(Uint8 axis, float value);
};

#endif // INPUTHANDLER_H