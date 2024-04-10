// fourier.h
// author: vishalpaudel
// 2024-04-06
// Note: For sampling a given `Sketch` (an array of `Vector2` vertices) as a continuous function

#ifndef FOURIER_SERIES_FOURIER_H
#define FOURIER_SERIES_FOURIER_H

#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

#include "math.h"
#include "complex.h"

#include "../include/sketch.h"
#include "../include/cycloid.h"

Vector2 sampleSketch(struct Sketch *sketch, double t);

Vector2 calculate_a(struct Sketch *sketch, int k);

bool updateFourier(struct Cycloid *cycloid, struct Sketch *sketch);

#endif //FOURIER_SERIES_FOURIER_H
