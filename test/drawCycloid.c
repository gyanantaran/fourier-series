// circles.c
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "../include/cycloid.h"
#include "../include/constants.h"


void updateCycloid(struct Cycloid * cycloid);
void drawCycloid(struct Cycloid *, Vector2 center);

int main(void)
{
    int numCycles = 9;
    struct Cycloid myCycloid;

    myCycloid = createCycloid(numCycles);
    double radius[] = {250, 50, 70, 100, 20, 25, 70, 30, 20};
    double omegas[] = {1.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0, 4.0, -4.0};
    double thetas[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
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
        // Update
        updateCycloid(&myCycloid);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Fourier Series Project", (int) (0.7 * SCREEN_WIDTH), (int) (0.1 * SCREEN_HEIGHT), 20, LIGHTGRAY);

        drawCycloid(&myCycloid, center);

        EndDrawing();
    }
    CloseWindow();

    freeCycloid(&myCycloid);

    return 0;
}

void drawCycloid(struct Cycloid * cycloid, Vector2 center)
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

        center = nextCenter;
    }
}

void updateCycloid(struct Cycloid * cycloid)
{
    // update the thetas using the omegas
    for( int i = 0; i < cycloid->numCycles; i++ ) {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (0.01 * (cycloid->omegas[i]));
    }
}