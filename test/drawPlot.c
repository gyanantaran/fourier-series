// drawCycloidSketch.c
// author: vishalpaudel

#include "../include/sketch.h"
#include "../include/cycloid.h"
#include "../include/constants.h"

#include "raylib.h"
#include "raymath.h"

Vector2 xloc = {100, 200};
Vector2 xsize     = {400, 200};

Vector2 yloc = {100, 500};
Vector2 ysize = {400, 200};

int main(void)
{
    int numCycles = 9;
    struct Cycloid myCycloid;
    struct Sketch mySketch;
    struct Sketch xplot, yplot;

    mySketch = createSketch();
    xplot = createSketch();
    yplot = createSketch();

    myCycloid = createCycloid(numCycles);
    double radius[] = {300, 150, 75, 70, 60, 50, 45, 20, 15, 15, 1};
    double omegas[] = {0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0, 8.0, -8.0, 30.0, -30.0};
    double thetas[] = {0, 1, 0, 1, 0, 3, 0, 0, 0};
    for (int i = 0; i < myCycloid.numCycles; i++)
    {
        myCycloid.radius[i] = radius[i];
        myCycloid.omegas[i] = omegas[i];
        myCycloid.thetas[i] = thetas[i];
    }


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series-project");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(BACKGROUND_COLOR);
        DrawText("Fourier Series Project", (0.7) * SCREEN_WIDTH, (0.1) * SCREEN_HEIGHT, 20, TEXT_COLOR);
        DrawText("Plotting Phasor Components", (0.05) * SCREEN_WIDTH, (0.1) * SCREEN_HEIGHT, 20, TEXT_COLOR);

        DrawText("X-component", (0.05) * SCREEN_WIDTH, (0.15) * SCREEN_HEIGHT, 20, TEXT_COLOR);
        DrawText("Y-component", (0.05) * SCREEN_WIDTH, (0.45) * SCREEN_HEIGHT, 20, TEXT_COLOR);

        Vector2 center = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
        Vector2 CENTER = center;
        for( int i = 0; i < numCycles; i++ )
        {
            double theta;
            double radius;
            Vector2 nextCenter;

            theta = myCycloid.thetas[i];
            radius = myCycloid.radius[i];

            Vector2 ray;
            ray = (Vector2) {cos(theta), -sin(theta)};
            ray = Vector2Scale(ray, radius);
            nextCenter = Vector2Add(center, ray);

            DrawCircleV(center, (float) (5.0 / (i + 1.0)), RAYWHITE);                     // the center points
            DrawCircleLinesV(center, (float) radius, CIRCUMFERENCE_COLOR);                   // the circumferences
            DrawLineV(center, nextCenter, RAYWHITE);         // the lines connecting the centers

            center = nextCenter;
        }

        EndDrawing();

        // appending point in path-array
        if (mySketch.index < 0)
        {
            mySketch.index = 0;
            mySketch.vertices[mySketch.index] = center;

            xplot.index = 0;
            xplot.vertices[xplot.index] = (Vector2) {xloc.x + (xsize.x) * (xplot.index) / MAX_VERTICES, -1 * (xsize.y) * (center.x - CENTER.x) / SCREEN_WIDTH + xloc.y + xsize.y / 2};

            yplot.index = 0;
            yplot.vertices[yplot.index] = (Vector2) {yloc.x + (ysize.x) * (yplot.index) / MAX_VERTICES, 1 * (ysize.y) * (center.y - CENTER.y) / SCREEN_HEIGHT + yloc.y + ysize.y / 2};
        }
        else
        {
            Vector2 vold, vnew;
            vold = mySketch.vertices[mySketch.index];
            vnew = center;

            if(Vector2Distance(vold, vnew) > DELTA_VERTICES)
            {
                mySketch.index = (mySketch.index + 1) % MAX_VERTICES;
                mySketch.vertices[mySketch.index] = vnew;

                xplot.index = (xplot.index + 1) % MAX_VERTICES;
                xplot.vertices[xplot.index] = (Vector2) {xloc.x + (xsize.x) * (xplot.index) / MAX_VERTICES, -1 * (xsize.y) * (vnew.x - CENTER.x) / SCREEN_WIDTH + xloc.y + xsize.y / 2};

                yplot.index = (yplot.index + 1) % MAX_VERTICES;
                yplot.vertices[yplot.index] = (Vector2) {yloc.x + (ysize.x) * (yplot.index) / MAX_VERTICES, 1 * (ysize.y) * (vnew.y - CENTER.y) / SCREEN_HEIGHT + yloc.y + ysize.y / 2};
            }
        }
        DrawLineStrip(mySketch.vertices, mySketch.index + 1, PEN_COLOR);
        DrawLineStrip(xplot.vertices, xplot.index + 1, PEN_COLOR);
        DrawLineStrip(yplot.vertices, yplot.index + 1, PEN_COLOR);

        DrawRectangleLines(xloc.x, xloc.y, xsize.x, xsize.y, LIGHTGRAY);
        DrawRectangleLines(yloc.x, yloc.y, ysize.x, ysize.y, LIGHTGRAY);

        // update the thetas using the omegas
        for( int i = 0; i < numCycles; i++ ) {
            // cycloid.thetas[i] += cycloid.omegas[i];
            myCycloid.thetas[i] += (0.005 * (myCycloid.omegas[i]));
        }
    }

    CloseWindow();

    freeCycloid(&myCycloid);
    freeSketch(&mySketch);
    freeSketch(&yplot);

    return 0;
}