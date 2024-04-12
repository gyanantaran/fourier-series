// drawFourier.c
// author: vishalpaudel
// 2024-04-06
// Note: for bringing everything together and drawing out the fourier series expansion of a sketch

#include "raylib.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"

#include "../include/fourier.h"

// Compare function for sorting floats
int compare_floats(const void *a, const void *b) {
    float fa = *((float*)a);
    float fb = *((float*)b);
    if (fa < fb) return -1;
    if (fa > fb) return 1;
    return 0;
}

// Function to find median of an array of floats
float find_median(float arr[], int n) {
    // Sort the array
    qsort(arr, n, sizeof(float), compare_floats);

    // Calculate median
    if (n % 2 == 0) {
        // If even number of elements, average of the middle two elements
        return (arr[n/2 - 1] + arr[n/2]) / 2.0;
    } else {
        // If odd number of elements, middle element
        return arr[n/2];
    }
}

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

    Vector2 center_of_the_screen = (Vector2) {(float) GetScreenWidth() / 2.0f, (float) GetScreenHeight() / 2.0f};
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
            myCycloid.SPEED = 0.001f;
        }
        if (update_camera) {
            const int N = 10;
            float points_x[N], points_y[N];

            // calculate ~average~ median point from last `N` points
            Vector2 avgPoint = {0, 0};
            for (int d = 0; d < N; d++) {
                Vector2 ith_point = myCycloidSketch.vertices[myCycloidSketch.index - d];

                points_x[d] = ith_point.x;
                points_y[d] = ith_point.y;
            }
            float x_median = -1 * find_median(points_x, N);
            float y_median = -1 * find_median(points_y, N);
            avgPoint = (Vector2) {x_median, y_median};

            camera.zoom = 20.0f;
            avgPoint = Vector2Scale(avgPoint, camera.zoom);
            camera.offset = Vector2Add(center_of_the_screen, avgPoint);

            myCycloid.SPEED = 0.0001f;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
        DrawText("Press SPACE to zoom-in/zoom-out", (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20,
                 LIGHTGRAY);

        BeginMode2D(camera);
        drawSketch(&mySketch, BLUE);
        if (finished_sketching) {
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