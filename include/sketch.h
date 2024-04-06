//
// Created by Vishal Paudel on 04/04/24.
//

#ifndef FOURIER_SERIES_SKETCH_H
#define FOURIER_SERIES_SKETCH_H
#include "raylib.h"

#define MAX_VERTICES 1000
#define DELTA_VERTICES 1

struct Sketch
{
    Vector2 * vertices;
    int index;
};

struct Sketch createSketch();

bool freeSketch(struct Sketch * sketch);

#endif //FOURIER_SERIES_SKETCH_H
