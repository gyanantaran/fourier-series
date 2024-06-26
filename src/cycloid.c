// cycloid.c
// author: vishalpaudel
// 2024-04-05
// Note: A cycloid is a custom structure representing data of a collection of
// circles

#include "../include/cycloid.h"

#include "raymath.h"

#include "../include/constants.h"

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

struct Cycloid createCycloid(int numCycles, Vector2 center) {
  printf("allocating cycloid...\n");

  struct Cycloid newCycloid;

  newCycloid.numCycles = numCycles;
  newCycloid.center = center;

  newCycloid.radius = (double *)calloc(MAX_CYCLOIDS, sizeof(double));
  newCycloid.thetas = (double *)calloc(MAX_CYCLOIDS, sizeof(double));
  newCycloid.omegas = (int *)calloc(MAX_CYCLOIDS, sizeof(int));
  newCycloid.outerPoints = (Vector2 *)calloc(MAX_CYCLOIDS, sizeof(Vector2));

  newCycloid.TIME_PERIOD = NORMAL_TIME_PERIOD;

  for (int k = 0; k < MAX_CYCLOIDS; k++) {
    // if index is odd then number should be +ve
    // so for example [0, 1, -1, 2, -2 ...]
    int sign = (2 * (k % 2) - 1);
    int value = (k + 1) / 2;
    newCycloid.omegas[k] = sign * value;
  }
  printf("...allocated cycloid\n");

  return newCycloid;
}

bool freeCycloid(struct Cycloid *cycloid) {
  printf("deallocating cycloid...\n");

  free(cycloid->radius);
  cycloid->radius = NULL;

  free(cycloid->thetas);
  cycloid->thetas = NULL;

  free(cycloid->omegas);
  cycloid->omegas = NULL;

  free(cycloid->outerPoints);
  cycloid->outerPoints = NULL;

  printf("...deallocated cycloid\n");

  return true;
}

void drawCycloid(struct Cycloid *cycloid) {
  Vector2 center = cycloid->center;
  DrawCircleV(center, (float)(5.0 / (0 + 1.0)), PEN_COLOR);

  Vector2 prevCenter, nextCenter;
  prevCenter = center;
  for (int i = 0; i < cycloid->numCycles; i++) {
    nextCenter = cycloid->outerPoints[i];

    // draw the center points
    DrawCircleV(prevCenter, (float)(5.0 / (i + 1.0)), PEN_COLOR);
    // draw the circumferences
    DrawCircleLinesV(prevCenter, (float)cycloid->radius[i],
                     CIRCUMFERENCE_COLOR);
    // draw the lines connecting the centers
    DrawLineV(prevCenter, nextCenter, PEN_COLOR);

    prevCenter = nextCenter;
  }
}

void updateCycloid(struct Cycloid *cycloid) {
  // update the thetas using the omegas
  Vector2 previousCenter, nextCenter;
  previousCenter = cycloid->center;
  for (int i = 0; i < cycloid->numCycles; i++) {
    // cycloid.thetas[i] += cycloid.omegas[i];
    float delta_time = GetFrameTime();
    cycloid->thetas[i] += delta_time * ((float)cycloid->omegas[i]) *
                          (2 * PI / cycloid->TIME_PERIOD);

    double theta = cycloid->thetas[i];
    double radius = cycloid->radius[i];

    // calculate next center
    Vector2 ray;
    ray.x = (float)(cos(theta));
    ray.y = (float)(sin(theta));

    ray = Vector2Scale(ray, (float)radius);
    nextCenter = Vector2Add(previousCenter, ray);
    cycloid->outerPoints[i] = nextCenter;

    previousCenter = nextCenter;
  }
}

// int main() {
//     int N = 100;
//     struct Cycloid myCycloid;
//
//     myCycloid = createCycloid(N);
//     freeCycloid(&myCycloid);
//
//     return 0;
// }