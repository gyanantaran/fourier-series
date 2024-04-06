// drawSample.c
// author: vishalpaudel
// Saturday, 6th April 2024
// Note: for demonstrating indexing and sampling from a sketch

#include "raylib.h"
#include "raymath.h"

#include "../include/sketch.h"
#include "../include/constants.h"

#include "../include/fourier.h"

void updateSketch(struct Sketch * mySketch);
void drawSketch(struct Sketch * mySketch);

int main() {
    struct Sketch mySketch;
    mySketch = createSketch();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);


    Vector2 sample = {0, 0};
    while (!WindowShouldClose()) {
        // Update
        updateSketch(&mySketch);

        // Draw
        BeginDrawing();

        // {{{
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Sketching - Fourier Series Project", (int) (0.6 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        // }}}

        drawSketch(&mySketch);

        // checking if mouse up === stopped sketching
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            double t = 0.5;
            sample = sampleSketch(&mySketch, t);
        }
        DrawCircle((int) sample.x, (int) sample.y, 30, PEN_COLOR);


        EndDrawing();
    }
    CloseWindow();

    freeSketch(&mySketch);

    return 0;
}


void drawSketch(struct Sketch * mySketch)
{
    if (mySketch->index > 0) {
        Vector2 vinit = mySketch->vertices[0], vlatest = mySketch->vertices[mySketch->index];

        DrawLineStrip(mySketch->vertices, mySketch->index + 1, PEN_COLOR);  // the whole sketch
        DrawLineV(vinit, vlatest, PEN_COLOR);                                // connecting first and last point
    }

    if (IsKeyPressed(KEY_E)) { mySketch->index = -1; ClearBackground(BACKGROUND_COLOR); }
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