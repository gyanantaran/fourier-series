// drawSketch.c
// author: vishalpaudel
// 2024-04-04
// Note: To demonstrate drawing figures onto the screen from the mouse

#include "../include/sketch.h"

int main() {
    struct Sketch mySketch;
    mySketch = createSketch();
    mySketch.connectFirstLast = true;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) updateSketch(&mySketch, GetMousePosition());

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Sketching - Fourier Series Project", (int) (0.6 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20,
                 TEXT_COLOR);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, TEXT_COLOR);
        DrawText(TextFormat("total elements: %d", mySketch.index + 1), (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20, TEXT_COLOR);

        // Draw Sketch
        drawSketch(&mySketch, TRACE_COLOR);
        EndDrawing();
    }
    CloseWindow();
    freeSketch(&mySketch);
    return 0;
}