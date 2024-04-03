// sketch.cpp
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

//#include "stdio.h"
#include <iostream>

Vector2 sketch[1000];
int sketch_index = -1;
double delta = 1;

int main() {
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "fourier-series-project");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Sketching - Fourier Series Project", (0.7) * screenWidth, (0.1) * screenHeight, 20, LIGHTGRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 vnew, vold;
            vnew = GetMousePosition();

            if (sketch_index < 0)
            {
                sketch_index = 0;
                sketch[sketch_index] = vnew;
            }
            else {
                vold = sketch[sketch_index];
                if (Vector2Distance(vnew, vold) > delta)
                {
                    sketch_index = (sketch_index + 1) % 1000;
                    sketch[sketch_index] = vnew;
                }
            }
        }
        DrawLineStrip(sketch, sketch_index + 1, BLACK);
        Vector2 vinit = sketch[0], vlatest = sketch[sketch_index];
        DrawLineV(vinit, vlatest, BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}