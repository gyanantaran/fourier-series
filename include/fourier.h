//
// Created by Vishal Paudel on 06/04/24.
//

#ifndef FOURIER_SERIES_FOURIER_H
#define FOURIER_SERIES_FOURIER_H

#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

#include "math.h"

#include "../include/sketch.h"


Vector2 sampleSketch(struct Sketch * sketch, double t);
Vector2 calculate_a(struct Sketch * sketch, int k);

#endif //FOURIER_SERIES_FOURIER_H
