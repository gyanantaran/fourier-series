// cycloid.h
// author: vishalpaudel
// 2024-04-05
// Note: A cycloid is a custom structure representing data of a collection of circles

#ifndef FOURIER_SERIES_CYCLOID_H
#define FOURIER_SERIES_CYCLOID_H

#include "raylib.h"
#include "raymath.h"

#include "constants.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MAX_CYCLOIDS 3000

// need to add ability to add cycloids
struct Cycloid {
    int numCycles;
    Vector2 center;

    double *radius;

    double *thetas;
    int *omegas;

    Vector2 *outerPoints;  // do I really need this here?

    float SPEED;   // do I really need this here?
};

struct Cycloid createCycloid(int numCycles, Vector2 center);

bool freeCycloid(struct Cycloid *cycloid);

void drawCycloid(struct Cycloid *cycloid);

void updateCycloid(struct Cycloid *cycloid);

#endif //FOURIER_SERIES_CYCLOID_H
