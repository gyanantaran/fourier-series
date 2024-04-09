// fourier.c
// author: vishalpaudel
// 2024-04-06
// Note: For sampling a given `Sketch` (an array of `Vector2` vertices) as a continuous function

#include "../include/fourier.h"

// synthesis equation  ==  Drawing out the phasors
// $\frac{1}{T} \sum \limits_{k=-\infnty}^{\infnty} a_k * e^{j k w_0 t}$

// analysis equation  ==  finding the radius and initial value
// $a_k = \int \limits_{t=-\infnty}^{\infnty} $


// time in seconds to complete one rotation
const double TIME_PERIOD = 1;
// granularity of data points in time
const double DELTA_TIME = 0.0001;
// the number of time points sampled everytime
const int MAX_TIME_POINTS = (int) (TIME_PERIOD / DELTA_TIME);

double w_0 = PI / TIME_PERIOD;


Vector2 sampleSketch(struct Sketch *sketch, double t) {
    // takes the index of the sketch to be a predictor of the time index
    // assumption, sampling of mouse location in the code will be in line with uniform time

    double real_index = t * (sketch->index);
    // printf("real index %f\n", real_index);
    int floor_index = floor(real_index);
    int ceil_index = ceil(real_index);

    // printf("calculated floor and ceil %d %d\n", floor_index, ceil_index);

    if (ceil_index == 0) return sketch->vertices[0];
    else if (floor_index == sketch->index) return sketch->vertices[sketch->index];
    else if (floor_index == ceil_index) return sketch->vertices[floor_index];
    else {   // doing linear interpolation between ceil and floor indexes
        double ceil_difference = (ceil_index - real_index);
        double floor_difference = (real_index - floor_index);

        Vector2 floor_point = sketch->vertices[floor_index];
        Vector2 ceil_point = sketch->vertices[ceil_index];

        Vector2 scaled_floor_point = Vector2Scale(floor_point, (float) ceil_difference);
        Vector2 scaled_ceil_point = Vector2Scale(ceil_point, (float) floor_difference);

        Vector2 linear_interpolated_point;
        linear_interpolated_point = Vector2Add(scaled_floor_point, scaled_ceil_point);
        // printf("Linear interpolated point: (%f, %f)\n", linear_interpolated_point.x, linear_interpolated_point.y);

        return linear_interpolated_point;
    }
}

Vector2 calculate_a(struct Sketch *sketch, int k) {
    Vector2 ak = {0, 0};
    for (int i = 0; i < MAX_TIME_POINTS; i++) {
        double t = ((float) i) / (float) MAX_TIME_POINTS;
        Vector2 x_t = sampleSketch(sketch, t);

        // calculating the complex exponent
        double kw_0t = (k * w_0) * t;
        Vector2 complex_exponent = {(float) cos(kw_0t), (float) sin(kw_0t)};

        // complex-multiplication
        double real_part = x_t.x * complex_exponent.x - x_t.y * complex_exponent.y;
        double imag_part = x_t.x * complex_exponent.y - x_t.y * complex_exponent.x;
        Vector2 x_t_into_complex_exponent_into_delta = {(float) real_part, (float) imag_part};
        x_t_into_complex_exponent_into_delta = Vector2Scale(x_t_into_complex_exponent_into_delta, (float) DELTA_TIME);

        ak = Vector2Add(x_t_into_complex_exponent_into_delta, ak);
    }
    return ak;
}

bool updateFourier(struct Cycloid *cycloid, struct Sketch *sketch) {
    for (int i = 0; i < cycloid->numCycles; i++) {
        int k = cycloid->omegas[i];
        Vector2 a_k = calculate_a(sketch, k);

        double radius, theta;
        radius = sqrt((double) (a_k.x * a_k.x + a_k.y * a_k.y));
        theta = atan((double) (a_k.y / a_k.x));
        // atan() function returns the values in the range of [-pi/2, pi/2]

        // arc tangent loses information
        // need to check quadrant
        // I OVERLOOKED THIS EARLIER and this was a MASSIVE bug
        if (a_k.x >= 0) {
            // Quadrant 1 or Quadrant 4
            theta = theta;
        } else if (a_k.x < 0) {
            // Quadrant 1 or Quadrant 4
            theta = PI + theta;
        }

        cycloid->radius[i] = radius;
        cycloid->thetas[i] = theta;
    }
    return true;
}