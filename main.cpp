#include <raylib.h>
#include "utils.hpp"
#include <iostream>
struct State
{
    Vector2 pos;
    float angle;
};
Color hexToRGBA(unsigned long hex)
{
    return Color{
        (unsigned char)((hex >> 24) & 0xff),
        (unsigned char)((hex >> 16) & 0xff),
        (unsigned char)((hex >> 8) & 0xff),
        (unsigned char)((hex) & 0xff),
    };
}
int main(int argc, char **argv)
{
    if (argc != 2 || !std::string(argv[1]).ends_with(".txt"))
    {
        std::cout << "Please provide a file name(.txt) as an argument\n";
        return 1;
    }
    Parameters params{};
    params.variables.emplace('+', CW);
    params.variables.emplace('-', ACW);
    params.variables.emplace('[', SAVE);
    params.variables.emplace(']', RESTORE);
    if (!parse(argv[1], params))
    {
        std::cout << "File '" << argv[1] << "' doesn't exist";
        return 1;
    };
    if (params.axiom.empty())
    {
        std::cout << "An axiom is required to start the L-system\n";
        return 1;
    }
    /*
        we apply rotation matrix to len vector <0,L> to get <-L*sin(theta),L*cos(theta)>
        then add the vector to start position to get end position <x - L*sin(theta), y - L*cos(theta)>
        note: we subtract L*cos(theta) from y since in pixel coordinates, y-axis moves down
    */
    float L = 20;
    float turn = params.turn * M_PI / 180;
    std::string curr = params.axiom;
    float sw = 960.0f, sh = 720.0f;
    InitWindow(sw, sh, "L-system");
    Color backgroundColor = hexToRGBA(params.background);
    Color foregroundColor = hexToRGBA(params.foreground);
    std::stack<State> stack;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            L *= 0.75f;
            std::string buffer = "";
            for (char ch : curr)
                buffer += params.rules.contains(ch) ? params.rules.at(ch) : std::string{ch};
            curr = buffer;
        }
        Vector2 pos{params.start_x, params.start_y};
        float angle = params.start_angle;
        BeginDrawing();
        ClearBackground(backgroundColor);
        for (char ch : curr)
        {
            if (!params.variables.contains(ch))
                continue;
            Action result = params.variables[ch];
            if (result == DRAW)
            {
                Vector2 newPos{pos.x - L * sinf(angle), pos.y - L * cosf(angle)};
                DrawLineV(pos, newPos, foregroundColor);
                pos = newPos;
            }
            else if (result == MOVE)
            {
                Vector2 newPos{pos.x - L * sinf(angle), pos.y - L * cosf(angle)};
                pos = newPos;
            }
            else if (result == ACW)
            {
                angle -= turn;
            }
            else if (result == CW)
            {
                angle += turn;
            }
            else if (result == SAVE)
            {
                stack.push({pos, angle});
            }
            else if (result == RESTORE)
            {
                State result = stack.top();
                pos = result.pos;
                angle = result.angle;
                stack.pop();
            }
            else if (result == STAY)
            {
                continue;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}