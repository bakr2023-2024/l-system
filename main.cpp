#include <raylib.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stack>
struct State
{
    Vector2 pos;
    float angle;
};
using namespace std;
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
    float L = 10;
    float turn = M_PI / 4;
    float scale = 1.0f / sqrtf(2);
    InitWindow(sw, sh, "L-system");
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            L *= scale;
            string buffer = "";
            for (char ch : curr)
            {
                if (ch == '1')
                    buffer += "11";
                else if (ch == '0')
                    buffer += "1[0]0";
                else
                    buffer += ch;
            }
            curr = buffer;
        }
        Vector2 pos{sw / 2, sh};
        float angle = 0.0f;
        stack<State> s;
        BeginDrawing();
        ClearBackground(BLACK);
        for (char ch : curr)
        {
            if (ch == '0')
            {
                Vector2 newPos{pos.x - L * sinf(angle), pos.y - L * cosf(angle)};
                DrawLineV(pos, newPos, WHITE);
                DrawEllipse(newPos.x, newPos.y, 2, 2, GREEN);
                pos = newPos;
            }
            else if (ch == '1')
            {
                Vector2 newPos{pos.x - L * sinf(angle), pos.y - L * cosf(angle)};
                DrawLineV(pos, newPos, WHITE);
                pos = newPos;
            }
            else if (ch == '[')
            {
                s.push({pos, angle});
                angle -= turn;
            }
            else if (ch == ']')
            {
                State state = s.top();
                pos = state.pos;
                angle = state.angle + turn;
                s.pop();
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}