// sketch.cpp
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "stdio.h"
#include "../include/sketch.h"

struct Sketch sketch;
double SKETCH_DELTA = 1;
int MAX_VERTICES = 1000;

int main() {
    sketch = createSketch();

    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "fourier-series-project");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        // Update

        // Draw
        BeginDrawing();

        // {{{
        ClearBackground(RAYWHITE);
        DrawText("Sketching - Fourier Series Project", (0.6) * screenWidth, (0.1) * screenHeight, 20, LIGHTGRAY);
        DrawText("Press E to Erase", (0.1) * screenWidth, (0.1) * screenHeight, 20, LIGHTGRAY);
        // }}}


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 vnew;
            vnew = GetMousePosition();

            if (sketch.index < 0) {
                printf("HELLLOOOOOOOOOOOOOO\n");
                sketch.index = 0;
                sketch.vertices[sketch.index] = vnew;
            } else {
                Vector2 vold;
                vold = sketch.vertices[sketch.index];
                if (Vector2Distance(vnew, vold) > SKETCH_DELTA) {
                    sketch.index = (sketch.index + 1) % MAX_VERTICES;
                    sketch.vertices[sketch.index] = vnew;
                }
            }
        }
        if (sketch.index > 0) {
            DrawLineStrip(sketch.vertices, sketch.index + 1, BLACK);
            Vector2 vinit = sketch.vertices[0], vlatest = sketch.vertices[sketch.index];
            DrawLineV(vinit, vlatest, BLACK);
        }

        if (IsKeyPressed(KEY_E)) { sketch.index = -1; ClearBackground(RAYWHITE); }

        EndDrawing();
    }
    CloseWindow();

    freeSketch(&sketch);

    return 0;
}