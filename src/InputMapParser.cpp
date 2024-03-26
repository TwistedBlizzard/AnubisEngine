#include "InputMapParser.hpp"

void InputMapParser::Parse(string filename)
{
    ifstream stream(filename);

    if (!stream.is_open())
    {
        cout << "Failed to open config file" << endl;
        return;
    }

    int line = 0;

    while(!stream.eof())
    {
        line++;

        string name;
        string buffer;

        stream >> name >> buffer;

        stringstream sstream(buffer);
        list<string> input;

        while (getline(sstream, buffer, '.'))
        {
            input.push_back(buffer);
        }

        InputType inputType = ParseInput(input);

        switch (inputType)
        {
        case GAMEPAD:
            ParseGamepad(name, input);
            break;
        default:
            cout << "Error: Invalid input type on line " << line  << " in " << filename << endl;
            break;
        }
    }

    stream.close();
}

InputType InputMapParser::ParseInput(list<string>& input)
{
    string inputType = input.front();
    input.pop_front();
    if (!InputLookup.contains(inputType))
        return ERROR;

    return InputLookup.at(inputType);
}

void InputMapParser::ParseGamepad(string name, list<string> input)
{
}

void InputMapParser::ParseKeyboard(string name, list<string> input)
{
}

void InputMapParser::ParseMouse(string name, list<string> input)
{
}
