// drawSVGFourier.c
// author: vishalpaudel
// 2024-04-06
// Note: for bringing everything together and drawing out the fourier series expansion of a sketch

#include "raylib.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"
#include "../include/readPoints.h"

#include "../include/fourier.h"

#include "rlgl.h"

#include <assert.h>

struct GameState {
    bool sketchingFinished;
    bool cameraZoomed;
    bool showAllHarmonics;
};

int compareX(const void *a, const void *b);

int compareY(const void *a, const void *b);

Vector2 find_median_point(Vector2 *points, int N);

void handleSketching(struct GameState *state, Camera2D *camera, struct Cycloid *myCycloid, struct Sketch *mySketch,
                     struct Sketch *myCycloidSketch);

void handleZooming(struct GameState *state);

void updateCamera(struct GameState *state, Camera2D *camera, struct Sketch *myCycloidSketch, struct Cycloid *myCycloid,
                  Vector2 offset);

void drawText();

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(MAX_FPS);

    struct Cycloid myCycloid = createCycloid(NUMBER_CYCLES, (Vector2) {(0), (0)});

    struct Sketch mySketch = readPointsFile(POINTS_FILE_PATH);
    struct Sketch myCycloidSketch = createSketch();
//    struct Sketch myCycloidSketch2 = createSketch();

    mySketch.connectFirstLast = true;
    updateFourier(&myCycloid, &mySketch);

    Vector2 offset = (Vector2) {(float) GetScreenWidth() / 2.0f, (float) GetScreenHeight() / 2.0f};

    Camera2D camera = {.target = {0, 0}, .offset = offset, .rotation = 0, .zoom = 1.0f};

    struct GameState gameState = {
            .sketchingFinished = false,
            .cameraZoomed = false,
            .showAllHarmonics = false
    };

    while (!WindowShouldClose()) {
        // Update
        handleSketching(&gameState, &camera, &myCycloid, &mySketch,
                        &myCycloidSketch); // state handling  --  Sketching Input from mouse

        updateCycloid(&myCycloid);
        updateSketch(&(myCycloidSketch), myCycloid.outerPoints[myCycloid.numCycles - 1]);

//        updateSketch(&(myCycloidSketch2), myCycloid.outerPoints[myCycloid.numCycles - 1 - 10]);

        handleZooming(&gameState);
        updateCamera(&gameState, &camera, &myCycloidSketch, &myCycloid, offset);

        // Draw
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        drawText();
        BeginMode2D(camera);
        drawSketch(&mySketch, BLUE);
        if (true) {
            drawCycloid(&myCycloid);

            drawSketch(&(myCycloidSketch), GREEN);

//            drawSketch(&(myCycloidSketch2), YELLOW);
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

void drawText() {
    DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
    DrawText("Press E to Erase", (int) (0.1 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);
    DrawText("Press SPACE to zoom-in/zoom-out", (int) (0.1 * SCREEN_WIDTH), (int) (0.2 * SCREEN_HEIGHT), 20,
             LIGHTGRAY);
    DrawText("Signals and Systems", (int) (0.6 * SCREEN_WIDTH), (int) (0.8 * SCREEN_HEIGHT), 20, LIGHTGRAY);
    DrawText("Vishal Paudel", (int) (0.6 * SCREEN_WIDTH), (int) (0.85 * SCREEN_HEIGHT), 20, LIGHTGRAY);
}

void handleSketching(struct GameState *state, Camera2D *camera, struct Cycloid *myCycloid, struct Sketch *mySketch,
                     struct Sketch *myCycloidSketch) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        state->sketchingFinished = false;

        myCycloidSketch->index = -1;
        updateSketch(mySketch, GetScreenToWorld2D(GetMousePosition(), *camera));

        if (state->cameraZoomed) mySketch->index = -1;
        state->cameraZoomed = false;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        state->sketchingFinished = true;
        updateFourier(myCycloid, mySketch);
        myCycloidSketch->index = -1;
    }
}

void handleZooming(struct GameState *state) {
    if (IsKeyPressed(KEY_SPACE)) {
        state->cameraZoomed = (bool) !(state->cameraZoomed);
        DrawRectangleV((Vector2) {0.09 * GetScreenWidth(), 0.19 * GetScreenHeight()}, (Vector2) {400, 50}, WHITE);
    }
}

void updateCamera(struct GameState *state, Camera2D *camera, struct Sketch *myCycloidSketch, struct Cycloid *myCycloid,
                  Vector2 offset) {
    float K = 7.0f;  // transition speed
    if (state->cameraZoomed) {
        const int N = 3;
        Vector2 last_few_points[N];

        // calculate ~average~ median point from last `N` points
        for (int d = 0; d < N; d++) { last_few_points[d] = myCycloidSketch->vertices[myCycloidSketch->index - d]; }
        Vector2 centerPoint = find_median_point(last_few_points, N);

        // transition, messy, but mathematical
        camera->zoom = camera->zoom + (ZOOM_AFTER_ZOOM - camera->zoom) / (10 * K);
        camera->offset = Vector2Add(Vector2Scale(
                                            Vector2Subtract(Vector2Add(offset, Vector2Scale(centerPoint, camera->zoom)), camera->offset), 1 / K),
                                    camera->offset);
        myCycloid->TIME_PERIOD = myCycloid->TIME_PERIOD + (AFTER_ZOOM_TIME_PERIOD - myCycloid->TIME_PERIOD) / K;
    } else if (!(state->cameraZoomed)) {
        // transition, messy, but mathematical
        camera->offset = Vector2Add(Vector2Scale(Vector2Subtract(offset, camera->offset), 1 / (10 * K)),
                                    camera->offset);
        camera->zoom = camera->zoom + (NORMAL_ZOOM - camera->zoom) / (5 * K);
        myCycloid->TIME_PERIOD = myCycloid->TIME_PERIOD + (NORMAL_TIME_PERIOD - myCycloid->TIME_PERIOD) / K;
    } else {
        assert(0 && "updateCamera: Unexpected branch reached!");
    }
}

// Define a comparison function to sort Vector2 objects based on x-coordinate
int compareX(const void *a, const void *b) {
    const Vector2 *va = (const Vector2 *) a;
    const Vector2 *vb = (const Vector2 *) b;
    return (va->x > vb->x) - (va->x < vb->x);
}

// Define a comparison function to sort Vector2 objects based on y-coordinate
int compareY(const void *a, const void *b) {
    const Vector2 *va = (const Vector2 *) a;
    const Vector2 *vb = (const Vector2 *) b;
    return (va->y > vb->y) - (va->y < vb->y);
}

Vector2 find_median_point(Vector2 *points, int N) {
    float median_x, median_y;
    // Find the median of x-coordinates
    qsort(points, N, sizeof(Vector2), compareX);

    if (N % 2 == 1) { median_x = points[N / 2].x; }
    else { median_x = 0.5f * (points[(N - 1) / 2].x + points[N / 2].x); }

    // Find the median of y-coordinates
    qsort(points, N, sizeof(Vector2), compareY);
    if (N % 2 == 1) { median_y = points[N / 2].y; }
    else { median_y = 0.5f * (points[(N - 1) / 2].y + points[N / 2].y); }

    // Return the median point
    Vector2 median_point = {-1.0f * median_x, -1.0f * median_y};
    return median_point;
}
