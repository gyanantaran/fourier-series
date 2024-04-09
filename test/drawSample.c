// drawSample.c
// author: vishalpaudel
// Saturday, 6th April 2024
// Note: for demonstrating indexing and sampling from a sketch

#include "raylib.h"
#include "raymath.h"

#include "../include/sketch.h"
#include "../include/constants.h"

#include "../include/fourier.h"

int main() {
    struct Sketch mySketch;
    mySketch = createSketch();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);
    Vector2 sample = {};
    double t = 0;
    double DELTA_TIME = 0.01;
    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) updateSketch(&mySketch, GetMousePosition());

        if (IsKeyDown(KEY_UP)) {
            t += DELTA_TIME;
            sample = sampleSketch(&mySketch, t);
        }
        if (IsKeyDown(KEY_DOWN)) {
            t -= DELTA_TIME;
            sample = sampleSketch(&mySketch, t);
        }

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Sampling - Fourier Series Project", (int) (0.6 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        DrawText(TextFormat("t: %f", t), (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText(TextFormat("sampled-point: {%f, %f}", sample.x, sample.y), (int) (0.1 * SCREEN_WIDTH), (int) (0.3 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        drawSketch(&mySketch, PEN_COLOR);

        DrawCircle((int) sample.x, (int) sample.y, 30, PEN_COLOR);
        EndDrawing();
    }
    CloseWindow();
    freeSketch(&mySketch);
    return 0;
}