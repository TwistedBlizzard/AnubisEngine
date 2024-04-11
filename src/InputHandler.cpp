#include "InputHandler.hpp"

InputHandler::InputHandler():
m_initialised(false),
m_mousePos(nullptr),
m_mouseRel(nullptr),
m_leftStick(nullptr),
m_rightStick(nullptr),
m_leftTrigger(nullptr),
m_rightTrigger(nullptr),
m_invertLeftX(false),
m_invertLeftY(false),
m_invertRightX(false),
m_invertRightY(false),
m_line(0)
{}

InputHandler::~InputHandler()
{}

void InputHandler::HandleEvent(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
    {
        if (event.key.repeat)
            break;
        SDL_Keycode key(event.key.keysym.sym);
        HandleKeyboard(key, true);
        break;
    }
    case SDL_EVENT_KEY_UP:
    {
        SDL_Keycode key(event.key.keysym.sym);
        HandleKeyboard(key, false);
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    {
        int button(event.button.button);
        HandleMouseButton(button, true);
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_UP:
    {
        int button(event.button.button);
        HandleMouseButton(button, true);
        break;
    }
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    {
        Uint8 button(event.gbutton.button);
        HandleGamepadButton(button, true);
        break;
    }
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
    {
        Uint8 button(event.gbutton.button);
        HandleGamepadButton(button, false);
        break;
    }
    case SDL_EVENT_MOUSE_MOTION:
    {
        float x(event.motion.x);
        float y(event.motion.y);
        float xrel(event.motion.xrel);
        float yrel(event.motion.yrel);
        HandleMouseMotion(x, y, xrel, yrel);
        break;
    }
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
    {
        Uint8 axis(event.gaxis.axis);
        float value(event.gaxis.value);
        HandleGamepadAxis(axis, value);
        break;
    }
    default:
        break;
    }
}

bool InputHandler::RegisterValue(InputMethod method, string input, bool *value)
{

    switch (method)
    {
    case KEYBOARD:
    {
        SDL_Keycode key = SDL_GetKeyFromName(input.c_str());

        if (key == SDLK_UNKNOWN)
        {
            cout << "Error: Invalid key: " << input << endl;
            return false;
        }

        if (m_keys.contains(key))
            cout << "Warning: Overwriting registered key: " << input << endl;

        m_keys[key] = value;

        break;
    }
    case MOUSE_BUTTON:
    {
        if (!MouseButtonLookup.contains(input))
        {
            cout << "Error: Invalid mouse button: " << input << endl;
            return false;
        }

        int button = MouseButtonLookup.at(input);

        if (m_mouseButtons.contains(button))
            cout << "Warning: Overwriting mouse button: " << input << endl;

        m_mouseButtons[button] = value;

        break;
    }
    case GAMEPAD_BUTTON:
    {
        SDL_GamepadButton button = SDL_GetGamepadButtonFromString(input.c_str());

        if (button == SDL_GAMEPAD_BUTTON_INVALID)
        {
            cout << "Error: Invalid gamepad button: " << input << endl;
            return false;
        }

        if (m_gamepadButtons.contains(button))
            cout << "Warning: Overwriting gamepad button: " << input << endl;

        m_gamepadButtons[button] = value;

        break;
    }
    default:
        cout << "Error: Invalid value type: bool" << endl;
        return false;
    }

    return true;
}

bool InputHandler::RegisterValue(InputMethod method, Vector2f *value)
{
    switch (method)
    {
    case MOUSE_POSITION:
        if (m_mousePos)
            cout << "Warning: Overwriting mouse absolute position" << endl;
        
        m_mousePos = value;
        
        break;
    case MOUSE_RELATIVE:
        if (m_mouseRel)
            cout << "Warning: Overwriting mouse relative position" << endl;

        m_mouseRel = value;

        break;
    case GAMEPAD_LEFT_STICK:
        if (m_leftStick)
            cout << "Warning: Overwriting gamepad left stick" << endl;

        m_leftStick = value;

        break;
    case GAMEPAD_RIGHT_STICK:
        if (m_rightStick)
            cout << "Warning: Overwriting gamepad right stick" << endl;

        m_rightStick = value;

        break;
    default:
        cout << "Error: Invalid value type: Vector2f" << endl;
        return false;
    }

    return true;
}

bool InputHandler::RegisterValue(InputMethod method, float *value)
{
    switch (method)
    {
    case GAMEPAD_LEFT_TRIGGER:
        if (m_leftTrigger)
            cout << "Warning: Overwriting gamepad left trigger" << endl;
        
        m_leftTrigger = value;

        break;
    case GAMEPAD_RIGHT_TRIGGER:
        if (m_rightTrigger)
            cout << "Warning: Overwriting gamepad right trigger" << endl;
        
        m_rightTrigger = value;

        break;
    default:
        cout << "Error: Invalid value type: float" << endl;
        return false;
    }

    return true;
}

void InputHandler::UnregisterValue(InputMethod method)
{

}

void InputHandler::UnregisterValue(InputMethod method, string input)
{
    
}

void InputHandler::HandleKeyboard(SDL_Keycode key, bool value)
{
    if (m_keys.contains(key))
        *(m_keys.at(key)) = value;
}

void InputHandler::HandleMouseButton(int button, bool value)
{
    if (m_mouseButtons.contains(button))
        *(m_mouseButtons.at(button)) = value;
}

void InputHandler::HandleGamepadButton(Uint8 button, bool value)
{
    if (m_gamepadButtons.contains(button))
        *(m_gamepadButtons.at(button)) = value;
}

void InputHandler::HandleMouseMotion(float x, float y, float xrel, float yrel)
{
    if (m_mousePos)
        *m_mousePos = Vector2f(x, y);

    if (m_mouseRel)
        *m_mouseRel = Vector2f(xrel, yrel);
}

void InputHandler::HandleGamepadAxis(Uint8 axis, float value)
{
    switch (axis)
    {
    case SDL_GAMEPAD_AXIS_LEFTX:
        if (m_leftStick)
            m_leftStick->x = value;
        break;
    case SDL_GAMEPAD_AXIS_LEFTY:
        if (m_leftStick)
            m_leftStick->y = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTX:
        if (m_rightStick)
            m_rightStick->y = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTY:
        if (m_rightStick)
            m_rightStick->y = value;
        break;
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
        if (m_leftTrigger)
            *m_leftTrigger = value;
        break;
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
        if (m_rightTrigger)
            *m_rightTrigger = value;
        break;
    default:
        break;
    }
}
