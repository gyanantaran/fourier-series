// circles.c
// author: vishalpaudel

#include "raylib.h"
#include "raymath.h"

#include "cycloid.h"


int N = 5;
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

void drawCycloid(Vector2 * center, float radius, Vector2 * outerPoint)
{
    DrawCircleV(*center, 5, BLACK);                     // the center points
    DrawCircleLinesV(*center, radius, BLACK);                   // the circumferences
    DrawLineV(*center, *outerPoint, BLACK);         // the lines connecting the centers
}

void updateTheta(struct Cycloid * cycloid)
{
    // update the thetas using the omegas
    for( int i = 0; i < N; i++ ) {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (0.01 * (i + 1));
    }
}

int main(void)
{
    cycloid = createCycloid(N);
    cycloid.radius[0] = 250;
    cycloid.radius[1] = 50;
    cycloid.radius[2] = 75;
    cycloid.radius[3] = 25;
    cycloid.radius[4] = 10;


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
        for( int i = 0; i < N; i++ )
        {
            double theta;
            double radius;
            Vector2 nextCenter;

            theta = cycloid.thetas[i];
            radius = cycloid.radius[i];
            nextCenter = calculateNextCenter(&center, radius, theta);   // find next cycloid center

            drawCycloid(&center, radius, &nextCenter);        // draw next cycloid

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