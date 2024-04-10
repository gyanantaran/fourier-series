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
    int numCycles = 90;
    struct Cycloid myCycloid;
    struct Sketch mySketch;
    struct Sketch xplot, yplot;

    mySketch = createSketch();
    xplot = createSketch();
    yplot = createSketch();

    myCycloid = createCycloid(numCycles, (Vector2) {SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0});
    for (int i = 0; i < myCycloid.numCycles; i++)
    {
        int omega = myCycloid.omegas[i];
        if (omega > 0 && (omega % 2 == 1))
        {
            myCycloid.radius[i] = 1000.0 / ((float) (i + 1) * PI );
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
    Vector2 center_of_the_screen = (Vector2) {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
    bool update_camera = false;
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

        BeginMode2D(camera);

        Vector2 center = {0, 0};
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

            center = GetScreenToWorld2D(center, camera);
            DrawCircleV(center, (float) (5.0 / (i + 1.0)), RAYWHITE);                     // the center points
            DrawCircleLinesV(center, (float) radius, CIRCUMFERENCE_COLOR);                   // the circumferences
            DrawLineV(center, nextCenter, RAYWHITE);         // the lines connecting the centers

            center = nextCenter;
        }
        EndMode2D();

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

        // shifting to the point's perspective
        camera.offset = (Vector2) {SCREEN_WIDTH/2.0 - camera.zoom * mySketch.vertices[mySketch.index].x, SCREEN_HEIGHT/2.0 - camera.zoom * mySketch.vertices[mySketch.index].y};


        BeginMode2D(camera);
        DrawLineStrip(mySketch.vertices, mySketch.index + 1, PEN_COLOR);
        EndMode2D();

        DrawLineStrip(xplot.vertices, xplot.index + 1, PEN_COLOR);
        DrawLineStrip(yplot.vertices, yplot.index + 1, PEN_COLOR);

        DrawRectangleLines(xloc.x, xloc.y, xsize.x, xsize.y, LIGHTGRAY);
        DrawRectangleLines(yloc.x, yloc.y, ysize.x, ysize.y, LIGHTGRAY);

        EndDrawing();

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