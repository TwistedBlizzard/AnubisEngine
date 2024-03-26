#ifndef INPUTMAPPARSER_H
#define INPUTMAPPARSER_H

#include <fstream>
using std::ifstream;
using std::ios;

#include <sstream>
using std::stringstream;
using std::getline;

#include "Core.hpp"

enum InputType
{
    GAMEPAD,
    KEYBOARD,
    MOUSE,
    ERROR
};

const map<string, InputType> InputLookup
{
    {"Gamepad", GAMEPAD},
    {"GamePad", GAMEPAD},
    {"gamepad", GAMEPAD},
    {"Keyboard", KEYBOARD},
    {"KeyBoard", KEYBOARD},
    {"keyboard", KEYBOARD},
    {"Mouse", MOUSE},
    {"mouse", MOUSE}
};

class InputMapParser
{
public:
    static void Parse(string filename);

private:
    static InputType ParseInput(list<string>& input);
    static void ParseGamepad(string name, list<string> input);
    static void ParseKeyboard(string name, list<string> input);
    static void ParseMouse(string name, list<string> input);
};

#endif // INPUTMAPPARSER_H