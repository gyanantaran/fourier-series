// drawFourier.c
// author: vishalpaudel
// 2024-04-06
// Note: for bringing everything together and drawing out the fourier series expansion of a sketch

#include "raylib.h"
#include "raymath.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"
#include "../include/fourier.h"


void updateCycloid(struct Cycloid *cycloid);

void drawCycloid(struct Cycloid *cycloid, Vector2 center, Vector2 *outerPoints);

void updateCycloidSketch(struct Sketch *cycloidSketch, Vector2 center);

void drawCycloidSketch(struct Sketch *cycloidSketch);

void updateSketch(struct Sketch *sketch, struct Cycloid *cycloid, struct Sketch * cycloidSketch, Camera2D camera);

void drawSketch(struct Sketch *sketch);

bool have_sketched = false;
int main(void) {
    int numCycles = 3;
    Vector2 *outerPoints = calloc(numCycles, sizeof(Vector2));
    int outerPointToFollow = numCycles - 1;

    struct Cycloid myCycloid;
    struct Sketch myCycloidSketch;
    struct Sketch mySketch;

    myCycloidSketch = createSketch();
    mySketch = createSketch();

    myCycloid = createCycloid(numCycles);
    double radius[] = {300, 150, 75, 50, 60, 40, 45, 25, 15, 25, 10};
    double thetas[] = {3, 1, 0, 1, 0, 3, 0, 0, 0, 0, 0};
    for (int i = 0; i < myCycloid.numCycles; i++) {
        myCycloid.radius[i] = radius[i];
        myCycloid.thetas[i] = thetas[i];
    }


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);

    Vector2 center = {(0), (0)};

    Camera2D camera;
    camera.target = (Vector2) {0, 0};
    camera.offset = (Vector2) {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
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
            drawCycloid(&myCycloid, center, outerPoints);
            drawCycloidSketch(&myCycloidSketch);
        }
        drawSketch(&mySketch);
        EndMode2D();

        EndDrawing();

        // Update
        if (have_sketched) {
            updateCycloid(&myCycloid);
            updateCycloidSketch(&myCycloidSketch, outerPoints[outerPointToFollow]);
        }
        updateSketch(&mySketch, &myCycloid, &myCycloidSketch, camera);
    }
    CloseWindow();

    freeCycloid(&myCycloid);
    freeSketch(&myCycloidSketch);
    freeSketch(&mySketch);

    free(outerPoints);

    return 0;
}

void drawCycloid(struct Cycloid *cycloid, Vector2 center, Vector2 *outerPoints) {
    for (int i = 0; i < cycloid->numCycles; i++) {
        double theta;
        double radius;
        Vector2 nextCenter;

        theta = cycloid->thetas[i];
        radius = cycloid->radius[i];

        // calculate next center
        Vector2 ray;
        ray = (Vector2) {cosf((float) theta), -sinf((float) theta)};
        ray = Vector2Scale(ray, (float) radius);
        nextCenter = Vector2Add(center, ray);

        // draw the center points
        DrawCircleV(center, (float) (5.0 / (i + 1.0)), PEN_COLOR);
        // draw the circumferences
        DrawCircleLinesV(center, (float) radius, CIRCUMFERENCE_COLOR);
        // draw the lines connecting the centers
        DrawLineV(center, nextCenter, PEN_COLOR);

        outerPoints[i] = nextCenter;
        center = nextCenter;
    }
}

void updateCycloid(struct Cycloid *cycloid) {
    // update the thetas using the omegas
    for (int i = 0; i < cycloid->numCycles; i++) {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (0.01 * (cycloid->omegas[i]));
    }
}

void drawCycloidSketch(struct Sketch *cycloidSketch) {
    DrawLineStrip(cycloidSketch->vertices, cycloidSketch->index + 1, YELLOW);
}

void updateCycloidSketch(struct Sketch *cycloidSketch, Vector2 center) {
    // appending point in path-array
    if (cycloidSketch->index < 0) {
        cycloidSketch->index = 0;
        cycloidSketch->vertices[cycloidSketch->index] = center;
    } else {
        Vector2 vold, vnew;
        vold = cycloidSketch->vertices[cycloidSketch->index];
        vnew = center;

        if (Vector2Distance(vold, vnew) > DELTA_VERTICES) {
            cycloidSketch->index = (cycloidSketch->index + 1) % MAX_VERTICES;
            cycloidSketch->vertices[cycloidSketch->index] = vnew;
        }
    }
}

void updateSketch(struct Sketch *sketch, struct Cycloid *cycloid, struct Sketch * cycloidSketch, Camera2D camera) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        cycloidSketch->index = -1;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 vnew;
        vnew = GetMousePosition();
        vnew = GetScreenToWorld2D(vnew, camera);

        if (sketch->index < 0) {
            sketch->index = 0;
            sketch->vertices[sketch->index] = vnew;
        } else {
            Vector2 vold;
            vold = sketch->vertices[sketch->index];
            if (Vector2Distance(vnew, vold) > DELTA_VERTICES) {
                sketch->index = (sketch->index + 1) % MAX_VERTICES;
                sketch->vertices[sketch->index] = vnew;
            }
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        cycloidSketch->index = -1;

        for (int i = 0; i < cycloid->numCycles; i++) {
            int k = cycloid->omegas[i];
            Vector2 a_k = calculate_a(sketch, k);

            double radius, theta;
            radius = sqrt((double) (a_k.x * a_k.x + a_k.y * a_k.y));
            theta = atan((double) (a_k.y / a_k.x));
            // atan() function returns the values in the range of [-pi/2, pi/2]

            // arc tangent loses information
            // need to check quadrant
            // I OVERLOOKED THIS EARLIER and this was a MASSIVE bug
            if (a_k.x >= 0)
            {
                // Quadrant 1 or Quadrant 4
                theta = theta;
            }
            else if (a_k.x < 0)
            {
                // Quadrant 1 or Quadrant 4
                theta = PI + theta;
            }

            cycloid->radius[i] = radius;
            cycloid->thetas[i] = theta;
        }
        have_sketched = true;
    }
}

void drawSketch(struct Sketch *sketch) {
    if (sketch->index > 0) {
        DrawLineStrip(sketch->vertices, sketch->index + 1, PEN_COLOR);
        Vector2 vinit = sketch->vertices[0], vlatest = sketch->vertices[sketch->index];
        DrawLineV(vinit, vlatest, PEN_COLOR);
    }

    if (IsKeyPressed(KEY_E)) {
        sketch->index = -1;
        ClearBackground(RAYWHITE);
    }
}
