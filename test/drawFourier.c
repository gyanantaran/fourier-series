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
    int numCycles = 90;
    Vector2 center = (Vector2) {(0), (0)};
    struct Cycloid myCycloid;
    struct Sketch mySketch;
    struct Sketch myCycloidSketch;
    mySketch = createSketch();
    mySketch.connectFirstLast = true;
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

    Vector2 center_of_the_screen = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    bool finished_sketching = false;
    bool update_camera = false;
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

        // state handling
        if (IsKeyPressed(KEY_SPACE)) {
            update_camera = !update_camera;
            if (!update_camera) {
                camera.offset = center_of_the_screen;
                camera.zoom = 1.0f;
            }
        }
        if (update_camera) {
            int N = 35;
            // calculate average point from last `N` points
            Vector2 avgPoint = {0, 0};
            for (int d = 0; d < N; d++) {
                Vector2 ith_point = myCycloidSketch.vertices[myCycloidSketch.index - d];
                avgPoint = Vector2Add(avgPoint, ith_point);
            }
            avgPoint = Vector2Scale(avgPoint, -1.0f / (float) N);

            camera.zoom = 5.5f;
            avgPoint = Vector2Scale(avgPoint, camera.zoom);
            camera.offset = Vector2Add(center_of_the_screen, avgPoint);
        }

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press SPACE to zoom-in/zoom-out", (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        BeginMode2D(camera);
        drawSketch(&mySketch, TRACE_COLOR);
        if (finished_sketching) {
            Vector2 curPoint = myCycloidSketch.vertices[myCycloidSketch.index];
            drawCycloid(&myCycloid);
            drawSketch(&(myCycloidSketch), GREEN);
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