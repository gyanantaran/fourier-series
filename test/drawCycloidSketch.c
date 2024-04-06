// circles.c
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "../include/cycloid.h"
#include "../include/sketch.h"
#include "../include/constants.h"


void updateCycloid(struct Cycloid * cycloid);
void drawCycloid(struct Cycloid * cycloid, Vector2 center, Vector2 * outerPoints);

void updateSketch(struct Sketch * mySketch, Vector2 center);
void drawSketch(struct Sketch * mySketch);

int main(void)
{
    int numCycles = 11;
    Vector2 * outerPoints = calloc(numCycles, sizeof(Vector2));
    int outerPointToFollow = 10;

    struct Cycloid myCycloid;
    struct Sketch mySketch;
    mySketch = createSketch();

    myCycloid = createCycloid(numCycles);
    double radius[] = {300, 150, 75, 70, 60, 50, 45, 20, 15, 15, 1};
    double omegas[] = {0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0, 8.0, -8.0, 30.0, -30.0};
    double thetas[] = {3, 1, 0, 1, 0, 3, 0, 0, 0};
    for (int i = 0; i < myCycloid.numCycles; i++)
    {
        myCycloid.radius[i] = radius[i];
        myCycloid.omegas[i] = omegas[i];
        myCycloid.thetas[i] = thetas[i];
    }


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);

    Vector2 center = {(float) (SCREEN_WIDTH/2.0), (float) (SCREEN_HEIGHT/2.0)};
    while (!WindowShouldClose())
    {
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        drawCycloid(&myCycloid, center, outerPoints);
        drawSketch(&mySketch);

        EndDrawing();

        // Update
        updateCycloid(&myCycloid);
        updateSketch(&mySketch, outerPoints[outerPointToFollow]);
    }
    CloseWindow();

    freeCycloid(&myCycloid);
    free(outerPoints);

    return 0;
}

void drawCycloid(struct Cycloid * cycloid, Vector2 center, Vector2 * outerPoints)
{
    for( int i = 0; i < cycloid->numCycles; i++ )
    {
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
        DrawCircleV(center, (float) (5.0 / (i + 1.0)), BLACK);
        // draw the circumferences
        DrawCircleLinesV(center, (float) radius, CIRCUMFERENCE_COLOR);
        // draw the lines connecting the centers
        DrawLineV(center, nextCenter, BLACK);

        outerPoints[i] = nextCenter;
        center = nextCenter;
    }
}

void updateCycloid(struct Cycloid * cycloid)
{
    // update the thetas using the omegas
    for( int i = 0; i < cycloid->numCycles; i++ )
    {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (0.01 * (cycloid->omegas[i]));
    }
}

void drawSketch(struct Sketch * mySketch)
{
    DrawLineStrip(mySketch->vertices, mySketch->index + 1, BLACK);
}

void updateSketch(struct Sketch * mySketch, Vector2 center)
{
    // appending point in path-array
    if (mySketch->index < 0)
    {
        mySketch->index = 0;
        mySketch->vertices[mySketch->index] = center;
    }
    else
    {
        Vector2 vold, vnew;
        vold = mySketch->vertices[mySketch->index];
        vnew = center;

        if(Vector2Distance(vold, vnew) > DELTA_VERTICES)
        {
            mySketch->index = (mySketch->index + 1) % MAX_VERTICES;
            mySketch->vertices[mySketch->index] = vnew;
        }
    }
}
