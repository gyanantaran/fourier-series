// drawing.h
// author: vishalpaudel
// date: 2024-07-11
// note: drawing is a collection of `sketch`(es)

#ifndef FOURIER_SERIES_DRAWING_H
#define FOURIER_SERIES_DRAWING_H

#include "sketch.h"

struct Drawing {
    struct Sketch *sketches;
    int numSketches;
};

struct Drawing createDrawing(int numSketches);

bool freeDrawing(struct Drawing * drawing);

#endif // FOURIER_SERIES_DRAWING_H
