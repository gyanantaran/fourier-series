// drawFourier.c
// author: vishalpaudel
// 2024-04-06
// Note: for bringing everything together and drawing out the fourier series expansion of a sketch

#include "raylib.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"

#include "../include/fourier.h"

bool have_sketched = false;

int main(void) {
    int numCycles = 20;

    struct Cycloid myCycloid;
    struct Sketch myCycloidSketch;
    struct Sketch mySketch;

    myCycloidSketch = createSketch();
    mySketch = createSketch();
    myCycloid = createCycloid(numCycles);

    double radius[] = {300, 150, 75, 50, 60, 40, 45, 25, 15, 25, 10};
    for (int i = 0; i < myCycloid.numCycles; i++) {
        myCycloid.radius[i] = radius[i];
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);

    Vector2 center = {(0), (0)};

    Camera2D camera;
    camera.target = (Vector2) {0, 0};
    camera.offset = (Vector2) {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    camera.rotation = (0 * PI / 2) * (180 / PI);
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        BeginMode2D(camera);

        if (have_sketched) {
            drawCycloid(&myCycloid, center);
            drawSketch(&(myCycloidSketch), TRACE_COLOR);
        }
        drawSketch(&mySketch, TRACE_COLOR);
        EndMode2D();
        EndDrawing();

        // Update
        if (have_sketched) {
            updateCycloid(&myCycloid);
            updateSketch(&(myCycloidSketch), myCycloid.outerPoints[myCycloid.numCycles - 1]);
        }
        updateSketch(&mySketch, GetScreenToWorld2D(GetMousePosition(), camera));
        updateFourier(&myCycloid, &mySketch);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) have_sketched = false;
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) have_sketched = true;
    }
    CloseWindow();

    freeCycloid(&myCycloid);
    freeSketch(&(myCycloidSketch));
    freeSketch(&mySketch);

    return 0;
}