// drawSVG.c
// author: vishalpaudel
// note: to read a point file and show the sketch on the screen

#include "../include/readPoints.h"

int main() {
    const char file_path[] = "../assets/points-svg/peanocurve.txt";
    struct Sketch point_sketch = readPointsFile(file_path);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        // drawing all sub-`sketch`es inside the `drawing`
        drawSketch(&point_sketch, PEN_COLOR);
        EndDrawing();
    }
    CloseWindow();
    freeSketch(&point_sketch);
    return 0;
}
