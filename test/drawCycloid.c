// circles.c
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "../include/cycloid.h"


int numCycles = 10;
struct Cycloid cycloid;


int path_index_filled = -1;
Vector2 lastHarmonicPath[1000] = {};

Vector2 calculateNextCenter(Vector2 * center, float radius, float theta)
{
    Vector2 nextCenter;
    Vector2 ray;
    ray = (Vector2) {cos(theta), -sin(theta)};
    ray = Vector2Scale(ray, radius);
    nextCenter = Vector2Add(*center, ray);
    return nextCenter;
}

void updateTheta(struct Cycloid * cycloid)
{
    // update the thetas using the omegas
    for( int i = 0; i < numCycles; i++ ) {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (0.01 * (cycloid->omegas[i]));
    }
}

int main(void)
{
    cycloid = createCycloid(numCycles);
    cycloid.radius[0] = 50;
    cycloid.radius[1] = 150;
    cycloid.radius[2] = 105;
    cycloid.radius[3] = 55;
    cycloid.radius[4] = 20;
    cycloid.radius[5] = 15;
    cycloid.radius[6] = 1;
    cycloid.radius[7] = 3;
    cycloid.radius[8] = 2;
    cycloid.radius[9] = 5;

    cycloid.omegas[0] = 1.0;
    cycloid.omegas[1] = 2.0;
    cycloid.omegas[2] = 3.0;
    cycloid.omegas[3] = 4.0;
    cycloid.omegas[4] = 5.0;
    cycloid.omegas[5] = 6.0;
    cycloid.omegas[6] = 7.0;
    cycloid.omegas[7] = 8.0;
    cycloid.omegas[8] = 9.0;
    cycloid.omegas[9] = 10.0;

    cycloid.thetas[0] = -0.2;
    cycloid.thetas[1] = 0.0;
    cycloid.thetas[2] = 0.0;
    cycloid.thetas[3] = -0.5;
    cycloid.thetas[4] = 0.8;
    cycloid.thetas[5] = 0.9;
    cycloid.thetas[6] = -0.8;
    cycloid.thetas[7] = 0.8;
    cycloid.thetas[8] = 0.0;
    cycloid.thetas[9] = 0.0;


    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "fourier-series-project");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Fourier Series Project", (0.7) * screenWidth, (0.1) * screenHeight, 20, LIGHTGRAY);

        Vector2 center = {screenWidth/2, screenHeight/2};
        for( int i = 0; i < numCycles; i++ )
        {
            double theta;
            double radius;
            Vector2 nextCenter;

            theta = cycloid.thetas[i];
            radius = cycloid.radius[i];
            nextCenter = calculateNextCenter(&center, (float) radius, (float) theta);   // find next cycloid center

            DrawCircleV(center, (float) (5.0 / (i + 1.0)), BLACK);                     // the center points
            DrawCircleLinesV(center, (float) radius, BLACK);                   // the circumferences
            DrawLineV(center, nextCenter, BLACK);         // the lines connecting the centers

            center = nextCenter;
        }

        EndDrawing();

        // appending point in path-array
        path_index_filled = (path_index_filled + 1) % 1000;
        lastHarmonicPath[path_index_filled] = center;
        DrawLineStrip(lastHarmonicPath, path_index_filled+1, BLACK);

        updateTheta(&cycloid);
    }
    CloseWindow();

    freeCycloid(&cycloid);

    return 0;
}