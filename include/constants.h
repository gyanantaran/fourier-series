// constants.h
// author: vishalpaudel

#ifndef FOURIER_SERIES_CONSTANTS_H
#define FOURIER_SERIES_CONSTANTS_H

#include "raylib.h" // for colors
#define CIRCUMFERENCE_COLOR LIGHTGRAY
#define BACKGROUND_COLOR BLACK
#define PEN_COLOR RAYWHITE
#define TEXT_COLOR LIGHTGRAY
#define TRACE_COLOR BLACK

#define POINTS_FILE_PATH "/Users/gyanantaran/Repos/fourier-series/assets/points-svg/fourier.txt"

#define MAX_FPS 60
#define NUMBER_CYCLES 200

#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH  1500

#define ZOOM_AFTER_ZOOM 20.0f
#define NORMAL_ZOOM 1.0f

#define AFTER_ZOOM_TIME_PERIOD (10000.0f * 1/ZOOM_AFTER_ZOOM)
#define NORMAL_TIME_PERIOD 100.0f

#define MAX_VERTICES 3000
#define DELTA_VERTICES 0.0

#define MAX_CYCLOIDS 3000

#endif //FOURIER_SERIES_CONSTANTS_H
