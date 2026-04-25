#include <raylib.h>
#include "utils.hpp"
#include <iostream>
struct State
{
    Vector2 pos;
    float angle;
};
int main(int argc, char **argv)
{
    if (argc != 2 || !std::string(argv[1]).ends_with(".txt"))
    {
        std::cout << "Please provide a file name(.txt) as an argument\n";
        return 1;
    }
    Parameters params{};
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
    float turn = params.angle * M_PI / 180;
    std::string curr = params.axiom;
    float sw = 960.0f, sh = 720.0f;
    InitWindow(sw, sh, "L-system");
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            L *= 0.9f;
            std::string buffer = "";
            for (char ch : curr)
                buffer += params.rules.contains(ch) ? params.rules.at(ch) : std::string{ch};
            curr = buffer;
        }
        Vector2 pos{10, sh};
        float angle = 0.0f;
        BeginDrawing();
        ClearBackground(BLACK);
        for (char ch : curr)
        {
            if (ch == 'F' || ch == 'G')
            {
                Vector2 newPos{pos.x - L * sinf(angle), pos.y - L * cosf(angle)};
                DrawLineV(pos, newPos, WHITE);
                pos = newPos;
            }
            else if (ch == '-')
            {
                angle -= turn;
            }
            else if (ch == '+')
            {
                angle += turn;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}