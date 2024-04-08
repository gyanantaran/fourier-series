// cycloid.c
// author: vishalpaudel
// 2024-04-05
// Note: A cycloid is a custom structure representing data of a collection of circles

#include "../include/cycloid.h"

struct Cycloid createCycloid(int numCycles) {
    printf("allocating cycloid...\n");

    struct Cycloid newCycloid;

    newCycloid.numCycles = numCycles;

    newCycloid.radius = (double *) calloc(newCycloid.numCycles, sizeof(double));
    newCycloid.thetas = (double *) calloc(newCycloid.numCycles, sizeof(double));
    newCycloid.omegas = (int *) calloc(newCycloid.numCycles, sizeof(int));
    newCycloid.outerPoints = (Vector2 *) calloc(newCycloid.numCycles, sizeof(Vector2));

    for (int k = 0; k < newCycloid.numCycles; k++) {
        // if index is odd then number should be +ve
        // so for example [0, 1, -1, 2, -2 ...]
        int sign = (2 * (k % 2) - 1);
        int value = (k + 1) / 2;
        newCycloid.omegas[k] = sign * value;
        printf("Value of omega %d\n", newCycloid.omegas[k]);
    }

    printf("allocated cycloid...\n");

    return newCycloid;
}

bool freeCycloid(struct Cycloid *cycloid) {
    printf("deallocating cycloid...\n");

    free(cycloid->radius);
    cycloid->radius = NULL;

    free(cycloid->thetas);
    cycloid->thetas = NULL;

    free(cycloid->omegas);
    cycloid->omegas = NULL;

    free(cycloid->outerPoints);
    cycloid->outerPoints = NULL;

    printf("deallocated cycloid...\n");

    return true;
}

void drawCycloid(struct Cycloid *cycloid, Vector2 center) {
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

        cycloid->outerPoints[i] = nextCenter;
        center = nextCenter;
    }
}


void updateCycloid(struct Cycloid * cycloid)
{
    double SPEED = 0.01;

    // update the thetas using the omegas
    for( int i = 0; i < cycloid->numCycles; i++ )
    {
        // cycloid.thetas[i] += cycloid.omegas[i];
        cycloid->thetas[i] += (SPEED * (cycloid->omegas[i]));
    }
}

//int main() {
//    int N = 100;
//    struct Cycloid myCycloid;
//
//    myCycloid = createCycloid(N);
//    freeCycloid(&myCycloid);
//
//    return 0;
//}