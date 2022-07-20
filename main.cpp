#include "raylib.h"
#include <stdlib.h>

int main(void)
{
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE  );
    InitWindow(800, 450, "raylib [core] example - basic window");
    while (!WindowShouldClose())
    {
            int h = 1000;
            int w = 1000;

            ClearBackground(RAYWHITE);
            Image image = GenImageColor(w, h, BLACK);
                for(int x = 0; x < h * w; x++) {
                    int r = rand() % 255;
                    int g = rand() % 255;
                    int b = rand() % 255;
                    ((u_int8_t *)image.data)[x * 4] = r;
                    ((u_int8_t *)image.data)[x * 4 + 1] = g;
                    ((u_int8_t *)image.data)[x * 4 + 2] = b;
                    ((u_int8_t *)image.data)[x * 4 + 3] = 255;
                }
        Texture texture = LoadTextureFromImage(image);
        BeginDrawing();
        DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
        UnloadTexture(texture);
        UnloadImage(image);
    }

    CloseWindow();

    return 0;
}
