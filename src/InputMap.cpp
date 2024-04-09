#include "InputMap.hpp"

bool ParseInputMap(InputMap& inputMap, ActionMap& actionMap)
{
    // Open file
    ifstream stream;
    stream.open("InputMap.conf");

    // Track line for error messages
    int line = 0;

    while (!stream.eof())
    {
        line++;

        // Read file
        string typeString, name, methodString, inputString, invertString;
        stream >> typeString >> name >> methodString >> inputString >> invertString;

        // Check type
        if (!TypeLookup.contains(typeString))
        {
            cout << "Error: Invalid type on line " << line << endl;
            return false;
        }

        InputType inputType = TypeLookup.at(typeString);
        
        // Check method
        if (!MethodLookup.contains(methodString))
        {
            cout << "Error: Invalid input method on line " << line << endl;
            return false;
        }

        InputMethod inputMethod = MethodLookup.at(methodString);

        // Check invert
        if (!InvertLookup.contains(invertString))
        {
            cout << "Error: Invalid invert option on line " << line << endl;
            return false;
        }

        // Create an action
        InputAction inputAction
        {
            InvertLookup.at(invertString),      // Invert:      bool
            1.0f,                               // Multiplier:  float
            name                                // Destination: string
        };

        // Get a valid value for the input
        int input = 0;
        bool readOk = GetInput(inputString, inputType, inputMethod, input);
        if (!readOk)
        {
            cout << "Error: Invalid input on line " << line << endl;
            return false;
        }

        // If it's not an alias, we're done
        if (name != "ALIAS")
        {
            actionMap[name] = inputType;
            inputMap[inputMethod][input] = inputAction;
            continue;
        }

        // Read alias name
        stream >> name;
        
        // Set the aliased action
        if (actionMap.contains(name))
        {
            inputAction.Destination = name;
        }
        else
        {
            cout << "Error Invalid alias on line " << line << endl;
            return false;
        }

        InputType destType = actionMap.at(name);

        // Check if we're mapping a bool to an axis
        if (inputType == BOOL && destType == AXIS)
        {
            string signString;
            stream >> signString;
            readOk = GetSign(inputAction, signString);
        }

        // Check if we read the sign ok
        if (!readOk)
        {
            cout << "Error: Invalid sign on line " << line << endl;
            return false;
        }

        // Write to the input map
        inputMap[inputMethod][input] = inputAction;
    }

    cout << "Success!" << endl;
    return true;
}

bool GetInput(string inputString, InputType inputType, InputMethod inputMethod, Sint32& input)
{
    switch (inputType)
    {
    case AXIS:
        return GetAxisInput(inputString, inputMethod, input);
    case BOOL:
        return GetBoolInput(inputString, inputMethod, input);
    case SCALAR:
        return GetScalarInput(inputString, inputMethod, input);
    default:
        cout << "Error: Unknown input type" << endl;
        return false;
    }
}

bool GetAxisInput(string inputString, InputMethod inputMethod, Sint32& input)
{
    switch (inputMethod)
    {
    case MOUSE_AXIS:
        if (!MouseAxisLookup.contains(inputString))
            return false;
        input = MouseAxisLookup.at(inputString);
        return true;
    case GAMEPAD_AXIS:
        input = SDL_GetGamepadAxisFromString(inputString.c_str());
        if (input == SDL_GAMEPAD_AXIS_INVALID)
            return false;
        return true;
    default:
        cout << "Error: Invalid input method" << endl;
        return false;
    }
}

bool GetBoolInput(string inputString, InputMethod inputMethod, Sint32& input)
{
    switch (inputMethod)
    {
    case MOUSE_BUTTON:
        if (!MouseButtonLookup.contains(inputString))
            return false;
        input = MouseButtonLookup.at(inputString);
        return true;
    case GAMEPAD_BUTTON:
        input = SDL_GetGamepadButtonFromString(inputString.c_str());
        if (input == SDL_GAMEPAD_BUTTON_INVALID)
            return false;
        return true;
    case KEYBOARD:
        input = SDL_GetKeyFromName(inputString.c_str());
        if (input == SDLK_UNKNOWN)
           return false;
        return true;
    default:
        cout << "Error: Unknown input method" << endl;
        return false;
    }
}

bool GetScalarInput(string inputString, InputMethod inputMethod, Sint32& input)
{
    if (inputMethod != GAMEPAD_AXIS)
        return false;

    if (!GetAxisInput(inputString, inputMethod, input))
        return false;

    switch (input)
    {
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
        return true;
    default:
        return false;
    }
}

bool GetSign(InputAction& InputAction, string signString)
{
    if (!SignLookup.contains(signString))
        return false;

    InputAction.Multiplier *= SignLookup.at(signString);
    
    return true;
}