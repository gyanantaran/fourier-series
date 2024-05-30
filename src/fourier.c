// fourier.c
// author: vishalpaudel
// 2024-04-06
// Note: For sampling a given `Sketch` (an array of `Vector2` vertices) as a continuous function

#include "../include/fourier.h"

#include "raymath.h"
#include "stdio.h"

#include "math.h"
#include "complex.h"

//const double TIME_PERIOD = 1;
const double DELTA_TIME = 0.0001;
const int MAX_TIME_POINTS = (int) (1 / DELTA_TIME);
double w_0 = 2 * PI; // / TIME_PERIOD;

bool updateFourier(struct Cycloid *cycloid, struct Sketch *sketch) {
    for (int i = 0; i < cycloid->numCycles; i++) {
        int k = cycloid->omegas[i];
        Vector2 a_k = calculate_a(sketch, k);
        double radius = sqrt((double) (a_k.x * a_k.x + a_k.y * a_k.y));
        double theta = atan((double) (a_k.y / a_k.x));
        if (a_k.x < 0) theta = PI + theta; // atan() range of [-pi/2, pi/2], but for Quadrant 2 or Quadrant 3
        cycloid->radius[i] = radius;
        cycloid->thetas[i] = theta;
    }
    return true;
}

// numerical integration
Vector2 calculate_a(struct Sketch *sketch, int k) {
    Vector2 ak = {0, 0};
    double t = 0;
    for (int m = 0; m < MAX_TIME_POINTS; m++) {
        Vector2 sample = sampleSketch(sketch, t);
        complex float x_t = CMPLXF(sample.x, sample.y);
        double exponent = -1 * (k * w_0) * t;
        Vector2 e_to_the_j_exponent = {(float) cos(exponent), (float) sin(exponent)};
        complex float complex_exponent = CMPLXF(e_to_the_j_exponent.x, e_to_the_j_exponent.y);
        complex float multiplied = x_t * complex_exponent * DELTA_TIME;
        Vector2 element = (Vector2) {(float) creal(multiplied), (float) cimag(multiplied)};
        ak = Vector2Add(element, ak);
        t += DELTA_TIME;
    }
    // ak = Vector2Scale(ak, (float) (1 / TIME_PERIOD));
    return ak;
}

Vector2 sampleSketch(struct Sketch *sketch, double t) {
    // takes the index of the sketch to be a predictor of the time index
    // assumption, sampling of mouse location in the code will be in line with uniform time
    if (t < 0) printf("t less than 0 received %f\n", t);
    if (t > 1) printf("t greater than 0 received %f\n", t);

    double real_index = t * (sketch->index + 1);
    int floor_index = floor(real_index);
    int ceil_index = ceil(real_index);

    // printf("calculated floor and ceil %d %d\n", floor_index, ceil_index);
    if (ceil_index == 0) return sketch->vertices[0];
    else if (floor_index == ceil_index) return sketch->vertices[floor_index];
    else {   // doing linear interpolation between ceil and floor indexes
        double ceil_difference = (ceil_index - real_index);
        double floor_difference = (real_index - floor_index);

        if (ceil_index == sketch->index + 1) ceil_index = 0;
        Vector2 floor_point = sketch->vertices[floor_index];
        Vector2 ceil_point = sketch->vertices[ceil_index];

        Vector2 scaled_floor_point = Vector2Scale(floor_point, (float) ceil_difference);
        Vector2 scaled_ceil_point = Vector2Scale(ceil_point, (float) floor_difference);

        Vector2 linear_interpolated_point;
        linear_interpolated_point = Vector2Add(scaled_floor_point, scaled_ceil_point);

        return linear_interpolated_point;
    }
}