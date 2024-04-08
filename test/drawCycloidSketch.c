// drawCycloidSketch.c
// author: vishalpaudel
// 2024-04-05
// Note: To demonstrate the `Cycloid` drawn alongside with the `Sketch` of the trace of any chosen `outerPoint`

#include "../include/cycloid.h"
#include "../include/sketch.h"

int main(void) {
    int numCycles = 11;
    int outerPointToFollow = 10;

    struct Cycloid myCycloid = createCycloid(numCycles);
    struct Sketch mySketch = createSketch();

    double radius[] = {300, 150, 75, 70, 60, 50, 45, 20, 15, 15, 1};
    for (int i = 0; i < myCycloid.numCycles; i++) myCycloid.radius[i] = radius[i];

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(MAX_FPS);

    Camera2D camera = {
            .target = {0, 0},
            .offset = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0},
            .rotation = 0,
            .zoom = 1.0f
    };
    Vector2 center = {(float) (0), (float) (0)};
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Cycloid Sketch - Fourier Series Project", (int) (0.6 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, TEXT_COLOR);
        DrawText(TextFormat("total elements: %d", mySketch.index + 1), (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20, TEXT_COLOR);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, TEXT_COLOR);

        BeginMode2D(camera);
        drawCycloid(&myCycloid, center);
        drawSketch(&mySketch, TRACE_COLOR);
        EndMode2D();
        EndDrawing();

        // Update
        updateCycloid(&myCycloid);
        updateSketch(&mySketch, myCycloid.outerPoints[outerPointToFollow]);
    }
    CloseWindow();
    freeCycloid(&myCycloid);
    freeSketch(&mySketch);
    return 0;
}