// drawCycloid.c
// author: vishalpaudel
// 2024-04-04

#include "../include/cycloid.h"

int main(void) {
    int numCycles = 9;
    struct Cycloid myCycloid;
    myCycloid = createCycloid(numCycles);

    double radius[] = {250, 50, 70, 100, 20, 25, 70, 30, 20};
    for (int i = 0; i < myCycloid.numCycles; i++) myCycloid.radius[i] = radius[i];

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);

    Vector2 center = {(float) (SCREEN_WIDTH / 2.0), (float) (SCREEN_HEIGHT / 2.0)};
    while (!WindowShouldClose()) {
        // Update
        updateCycloid(&myCycloid);
        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, TEXT_COLOR);
        // Draw the cycloid
        drawCycloid(&myCycloid, center);
        EndDrawing();
    }
    CloseWindow();
    freeCycloid(&myCycloid);
    return 0;
}