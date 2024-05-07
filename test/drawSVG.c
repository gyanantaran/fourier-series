// drawSVG.c
// author: vishalpaudel
// note: to read a point file and show the sketch on the screen

#include "../include/readPoints.h"

int main() {
    const char file_path[] = "/Users/gyanantaran/Repos/fourier-series/assets/points-svg/music.txt";
    struct Drawing drawing = readPointsFile(file_path);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        // drawing all sub-`sketch`es inside the `drawing`
        for (int i = 0; i < drawing.numSketches; i++) { drawSketch(&drawing.sketches[i], TRACE_COLOR); }
        EndDrawing();
    }
    CloseWindow();
    freeDrawing(&drawing);
    return 0;
}
