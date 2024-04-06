// sketch.cpp
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "../include/sketch.h"
#include "../include/constants.h"

void updateSketch(struct Sketch * mySketch);
void drawSketch(struct Sketch * mySketch);

int main() {
    struct Sketch mySketch;
    mySketch = createSketch();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        // Update
        updateSketch(&mySketch);

        // Draw
        BeginDrawing();

        // {{{
        ClearBackground(RAYWHITE);
        DrawText("Sketching - Fourier Series Project", (int) (0.6 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        // }}}

        drawSketch(&mySketch);

        EndDrawing();
    }
    CloseWindow();

    freeSketch(&mySketch);

    return 0;
}


void drawSketch(struct Sketch * mySketch)
{
    if (mySketch->index > 0) {
        DrawLineStrip(mySketch->vertices, mySketch->index + 1, BLACK);
        Vector2 vinit = mySketch->vertices[0], vlatest = mySketch->vertices[mySketch->index];
        DrawLineV(vinit, vlatest, BLACK);
    }

    if (IsKeyPressed(KEY_E)) { mySketch->index = -1; ClearBackground(RAYWHITE); }
}

void updateSketch(struct Sketch * mySketch)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 vnew;
        vnew = GetMousePosition();

        if (mySketch->index < 0) {
            mySketch->index = 0;
            mySketch->vertices[mySketch->index] = vnew;
        } else {
            Vector2 vold;
            vold = mySketch->vertices[mySketch->index];
            if (Vector2Distance(vnew, vold) > DELTA_VERTICES) {
                mySketch->index = (mySketch->index + 1) % MAX_VERTICES;
                mySketch->vertices[mySketch->index] = vnew;
            }
        }
    }
}