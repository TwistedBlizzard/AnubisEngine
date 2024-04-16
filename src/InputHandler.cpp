#include "InputHandler.hpp"

#define DEFAULT_AXIS_THRESHOLD 2000

InputHandler::InputHandler():
m_initialised(false),
m_gamepad(nullptr),
m_mousePos(nullptr),
m_mouseRel(nullptr),
m_leftStick(nullptr),
m_rightStick(nullptr),
m_leftTrigger(nullptr),
m_rightTrigger(nullptr),
m_mouseMotion(nullptr),
m_invertLeftX(false),
m_invertLeftY(false),
m_invertRightX(false),
m_invertRightY(false),
m_line(0)
{
    m_thresholds =
    {
        {"LeftX",           DEFAULT_AXIS_THRESHOLD},
        {"LeftY",           DEFAULT_AXIS_THRESHOLD},
        {"RightX",          DEFAULT_AXIS_THRESHOLD},
        {"RightY",          DEFAULT_AXIS_THRESHOLD},
        {"LeftTrigger",     DEFAULT_AXIS_THRESHOLD},
        {"RightTrigger",    DEFAULT_AXIS_THRESHOLD}
    };
}

InputHandler::~InputHandler()
{}

void InputHandler::HandleEvent(const SDL_Event &event)
{
    if (!m_initialised)
    {
        int count;
        SDL_JoystickID* gamepads = SDL_GetGamepads(&count);

        if (count > 0)
            m_gamepad = SDL_OpenGamepad(gamepads[0]);

        SDL_free(gamepads);

        m_initialised = true;
    }

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
        HandleMouseButton(button, false);
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
        Sint16 value(event.gaxis.value);
        HandleGamepadAxis(axis, value);
        break;
    }
    case SDL_EVENT_GAMEPAD_ADDED:
    {
        if (!m_gamepad)
            m_gamepad = SDL_OpenGamepad(event.gdevice.which);
        break;
    }
    case SDL_EVENT_GAMEPAD_REMOVED:
    {
        if (m_gamepad && m_gamepad == SDL_GetGamepadFromInstanceID(event.gdevice.which))
            m_gamepad = nullptr;
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

bool InputHandler::RegisterValue(InputMethod method, bool *value)
{
    switch (method)
    {
    case MOUSE_POSITION:
    case MOUSE_RELATIVE:
        if (m_mouseMotion)
            cout << "Warning: Overwriting mouse motion" << endl;

        m_mouseMotion = value;

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

    if (m_mouseMotion)
        *m_mouseMotion = true;
}

void InputHandler::HandleGamepadAxis(Uint8 axis, Sint16 value)
{
    switch (axis)
    {
    case SDL_GAMEPAD_AXIS_LEFTX:
        if (abs(value) < m_thresholds.at("LeftX"))
            value = 0;
        if (m_leftStick)
            m_leftStick->x = float(value) / SDL_MAX_SINT16;
        break;
    case SDL_GAMEPAD_AXIS_LEFTY:
        if (abs(value) < m_thresholds.at("LeftY"))
            value = 0;
        if (m_leftStick)
            m_leftStick->y = float(value) / SDL_MAX_SINT16;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTX:
        if (abs(value) < m_thresholds.at("RightX"))
            value = 0;
        if (m_rightStick)
            m_rightStick->x = float(value) / SDL_MAX_SINT16;
        break;
    case SDL_GAMEPAD_AXIS_RIGHTY:
        if (abs(value) < m_thresholds.at("RightY"))
            value = 0;
        if (m_rightStick)
            m_rightStick->y = float(value) / SDL_MAX_SINT16;
        break;
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
        if (abs(value) < m_thresholds.at("LeftTrigger"))
            value = 0;
        if (m_leftTrigger)
            *m_leftTrigger = float(value) / SDL_MAX_SINT16;
        break;
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
        if (abs(value) < m_thresholds.at("RightTrigger"))
            value = 0;
        if (m_rightTrigger)
            *m_rightTrigger = float(value) / SDL_MAX_SINT16;
        break;
    default:
        break;
    }

    if (m_mouseMotion)
        *m_mouseMotion = false;
}

void InputHandler::SetThreshold(string axis, float threshold)
{
    if (!m_thresholds.contains(axis))
    {
        cout << "Error: Invalid axis: " << axis << endl;
        return;
    }

    if (threshold < 0.0f)
    {
        cout << "Error: Threshold must be greater than 0" << endl;
        return;
    }

    if (threshold >= 1.0f)
    {
        cout << "Error: Thresholg must be less than 1" << endl;
        return;
    }

    threshold *= SDL_MAX_SINT16;

    m_thresholds[axis] = Sint16(threshold);
}

void InputHandler::SetDefaultThreshold(string axis)
{
    if (!m_thresholds.contains(axis))
    {
        cout << "Error: Invalid axis: " << axis << endl;
        return;
    }

    m_thresholds[axis] = DEFAULT_AXIS_THRESHOLD;
}
