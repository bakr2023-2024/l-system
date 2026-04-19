#include <raylib.h>
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    string curr = argv[1]; // axiom
    float sw = 960.0f, sh = 720.0f;
    InitWindow(sw, sh, "L-system");
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
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
            cout << "current: " << curr << endl;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}