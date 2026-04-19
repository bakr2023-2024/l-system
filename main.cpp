#include <raylib.h>
#include "utils.hpp"
using namespace std;
struct State
{
    Vector2 pos;
    float angle;
};
int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    string curr = argv[1]; // axiom
    float sw = 960.0f, sh = 720.0f;
    /*
        we apply rotation matrix to len vector <0,L> to get <-L*sin(theta),L*cos(theta)>
        then add the vector to start position to get end position <x - L*sin(theta), y - L*cos(theta)>
        note: we subtract L*cos(theta) from y since in pixel coordinates, y-axis moves down
    */
    float L = 20;
    float turn = 2 * M_PI / 3.0;
    InitWindow(sw, sh, "L-system");
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            L *= 0.9f;
            string buffer = "";
            for (char ch : curr)
            {
                if (ch == 'F')
                    buffer += "F-G+F+G-F";
                else if (ch == 'G')
                    buffer += "GG";
                else
                    buffer += ch;
            }
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