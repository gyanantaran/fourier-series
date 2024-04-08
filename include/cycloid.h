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

struct Cycloid {
    int numCycles;

    double *radius;

    double *thetas;
    int *omegas;

    Vector2 *outerPoints;
};

struct Cycloid createCycloid(int numCycles);

bool freeCycloid(struct Cycloid *cycloid);

void drawCycloid(struct Cycloid *cycloid, Vector2 center);

void updateCycloid(struct Cycloid *cycloid);

#endif //FOURIER_SERIES_CYCLOID_H
