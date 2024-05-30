// cycloid.h
// author: vishalpaudel
// 2024-04-05
// Note: A cycloid is a custom structure representing data of a collection of circles

#ifndef FOURIER_SERIES_CYCLOID_H
#define FOURIER_SERIES_CYCLOID_H

#include "raylib.h"

// need to add ability to add cycloids
struct Cycloid {
    int numCycles;
    Vector2 center;

    double *radius;

    double *thetas;
    int *omegas;

    Vector2 *outerPoints;  // do I really need this here?

    float TIME_PERIOD;  // breaking change: removed speed variable
};

struct Cycloid createCycloid(int numCycles, Vector2 center);

bool freeCycloid(struct Cycloid *cycloid);

void drawCycloid(struct Cycloid *cycloid);

void updateCycloid(struct Cycloid *cycloid);

#endif //FOURIER_SERIES_CYCLOID_H
