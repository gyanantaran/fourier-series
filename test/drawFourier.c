// drawFourier.c
// author: vishalpaudel
// 2024-04-06
// Note: for bringing everything together and drawing out the fourier series expansion of a sketch

#include "raylib.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"

#include "../include/fourier.h"

int main(void) {
    int numCycles = 20;
    Vector2 center = (Vector2) {(0), (0)};
    struct Cycloid myCycloid;
    struct Sketch mySketch;
    struct Sketch myCycloidSketch;
    mySketch = createSketch(); mySketch.connectFirstLast = true;
    myCycloidSketch = createSketch();
    myCycloid = createCycloid(numCycles, center);
    for (int i = 0; i < myCycloid.numCycles; i++) {
        int omega = myCycloid.omegas[i];
        if (omega > 0 && (omega % 2 == 1)) {
            myCycloid.radius[i] = 1000.0 / ((float) (i + 1) * PI);
        }
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);
    Camera2D camera = {
            .target = {0, 0},
            .offset = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0},
            .rotation = 0,
            .zoom = 1.0f
    };

    bool finished_sketching = false;
    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            finished_sketching = false;
            updateSketch(&mySketch, GetScreenToWorld2D(GetMousePosition(), camera));
            myCycloidSketch.index = -1;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            finished_sketching = true;
            updateFourier(&myCycloid, &mySketch);
            myCycloidSketch.index = -1;
        }
        updateCycloid(&myCycloid);
        updateSketch(&(myCycloidSketch), myCycloid.outerPoints[myCycloid.numCycles - 1]);

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        BeginMode2D(camera);
        drawSketch(&mySketch, TRACE_COLOR);
        if (finished_sketching) {
            Vector2 curPoint = myCycloidSketch.vertices[myCycloidSketch.index];
            drawCycloid(&myCycloid);
            drawSketch(&(myCycloidSketch), TRACE_COLOR);
        }
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    freeCycloid(&myCycloid);
    freeSketch(&(myCycloidSketch));
    freeSketch(&mySketch);
    return 0;
}