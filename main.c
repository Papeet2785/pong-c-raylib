#include <stdlib.h>
#include <time.h>
#include "include/raylib.h"

#define BG_COLOR BLACK
#define FG_COLOR WHITE

int main() {

    const float WIDTH = 1024.0f;
    const float HEIGHT = 768.0f;
    const float MENU_FONT_SIZE = 0.05f * WIDTH;

    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "PONG");
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawRectangle(0.1f * WIDTH, 0.1f * HEIGHT, 0.3f * WIDTH, 0.3f * HEIGHT, FG_COLOR);
        DrawText("2 PLAYER", 0.125f * WIDTH, 0.22f * HEIGHT, MENU_FONT_SIZE, BG_COLOR);

        DrawRectangle(0.6f * WIDTH, 0.1 * HEIGHT, 0.3f * WIDTH, 0.3 * HEIGHT, FG_COLOR);
        DrawText("NO CPU", 0.655f * WIDTH, 0.22f * HEIGHT, MENU_FONT_SIZE, BG_COLOR);

        DrawRectangle(0.1f * WIDTH, 0.6f * HEIGHT, 0.3f * WIDTH, 0.3f * HEIGHT, FG_COLOR);
        DrawText("EZ CPU", 0.155f * WIDTH, 0.72f * HEIGHT, MENU_FONT_SIZE, BG_COLOR);

        DrawRectangle(0.6f * WIDTH, 0.6f * HEIGHT, 0.3f * WIDTH, 0.3f * HEIGHT, FG_COLOR);
        DrawText("IMPOSSIBLE", 0.61f * WIDTH, 0.72f * HEIGHT, 0.9f * MENU_FONT_SIZE, BG_COLOR);

        EndDrawing();

    };
    CloseWindow();

    return 0;
    
}