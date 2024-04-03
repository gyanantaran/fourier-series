// cycloid.h
// author: vishalpaudel

#ifndef FOURIER_SERIES_CYCLOID_H
#define FOURIER_SERIES_CYCLOID_H

#include <stdlib.h>
#include <stdbool.h>

struct Cycloid
{
    int numCycles;

    double *radius;

    double *thetas;
    double *omegas;
};

struct Cycloid createCycloid(int numCycles);

bool freeCycloid(struct Cycloid *cycloid);

#endif //FOURIER_SERIES_CYCLOID_H
