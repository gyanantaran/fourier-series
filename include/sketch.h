// sketch.h
// author: vishalpaudel
// 2024-04-04
// Note: A data structure wrapper for a bunch of Vector2 with an index

#ifndef FOURIER_SERIES_SKETCH_H
#define FOURIER_SERIES_SKETCH_H

#include "raylib.h"
#include "raymath.h"

#include "stdlib.h"
#include "stdio.h"

#include "constants.h"

#define MAX_VERTICES 1000
#define DELTA_VERTICES 1

struct Sketch {
    Vector2 *vertices;
    int index;

    bool connectFirstLast;  //
};

struct Sketch createSketch();

bool freeSketch(struct Sketch *sketch);

void drawSketch(struct Sketch *sketch, Color color);

void updateSketch(struct Sketch *mySketch, Vector2 newPoint);

#endif //FOURIER_SERIES_SKETCH_H
