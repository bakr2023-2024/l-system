
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stack>
#include <unordered_map>
#include <fstream>
enum Action
{
    DRAW,
    MOVE,
    STAY,
    CW,
    ACW,
    SAVE,
    RESTORE
};
Action strToAction(const std::string &str)
{
    if (str == "DRAW")
        return DRAW;
    if (str == "MOVE")
        return MOVE;
    if (str == "STAY")
        return STAY;
    if (str == "CW")
        return CW;
    if (str == "ACW")
        return ACW;
    if (str == "SAVE")
        return SAVE;
    if (str == "RESTORE")
        return RESTORE;
    return STAY;
}
struct Parameters
{
    std::unordered_map<char, Action> variables;
    std::unordered_map<char, std::string> rules;
    std::string axiom;
    float turn = 0.0f;
    float start_x = 0.0f, start_y = 0.0f;
    float start_angle = 0.0f;
    float length = 20;
    float scale = 0.75;
    unsigned long background = 0x000000ff;
    unsigned long foreground = 0xffffffff;
};
bool parse(std::string filename, Parameters &params)
{
    std::ifstream file(filename);
    if (!file)
        return false;
    std::string str;
    while (std::getline(file, str))
    {
        if (str == "[variables]")
        {
            while (std::getline(file, str) && !str.empty())
            {
                int delimIdx = str.find('=');
                if (delimIdx != std::string::npos)
                    params.variables.emplace(str.substr(0, delimIdx)[0], strToAction(str.substr(delimIdx + 1)));
            }
        }
        if (str == "[rules]")
        {
            while (std::getline(file, str) && !str.empty())
            {
                int delimIdx = str.find('=');
                if (delimIdx != std::string::npos)
                    params.rules.emplace(str.substr(0, delimIdx)[0], str.substr(delimIdx + 1));
            }
        }
        if (str == "[parameters]")
        {
            while (std::getline(file, str) && !str.empty())
            {
                int delimIdx = str.find('=');
                if (delimIdx != std::string::npos)
                {
                    std::string key = str.substr(0, delimIdx);
                    std::string val = str.substr(delimIdx + 1);
                    if (key == "axiom")
                        params.axiom = val;
                    else if (key == "turn")
                        params.turn = std::stof(val);
                    else if (key == "start_angle")
                        params.start_angle = std::stof(val);
                    else if (key == "start_x")
                        params.start_x = std::stof(val);
                    else if (key == "start_y")
                        params.start_y = std::stof(val);
                }
            }
        }
        if (str == "[misc]")
        {
            while (std::getline(file, str) && !str.empty())
            {
                int delimIdx = str.find('=');
                if (delimIdx != std::string::npos)
                {
                    std::string key = str.substr(0, delimIdx);
                    std::string val = str.substr(delimIdx + 1);
                    if (key == "background")
                        params.background = std::stoul(val, nullptr, 0);
                    else if (key == "foreground")
                        params.foreground = std::stoul(val, nullptr, 0);
                    else if (key == "length")
                        params.length = std::stof(val);
                    else if (key == "scale")
                        params.scale = std::stof(val);
                }
            }
        }
    }
    file.close();
    return true;
}