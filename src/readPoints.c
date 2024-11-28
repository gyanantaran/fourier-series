// readPoints.c

#include "../include/readPoints.h"

#include "../include/constants.h"

#include "math.h"
#include "raymath.h"

#include "stdio.h"
#include "stdlib.h"

struct Sketch readPointsFile(const char *filename) {
  FILE *file = fopen(filename, "r"); // Open the file for reading
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  } else {
    printf("Reading the points-file!\n");
  }

  struct Sketch point_sketch = createSketch();
  float left = INFINITY, right = -1 * INFINITY, top = INFINITY,
        bottom = -1 * INFINITY;

  int numVertices;
  fscanf(file, "%d",
         &numVertices); // Read the number of rows in the current section

  for (int j = 0; j < numVertices; j++) {
    float x, y;
    fscanf(file, "%f %f", &x, &y); // Read two numbers from the current row

    if (x < left)
      left = x;
    if (x > right)
      right = x;
    if (y < top)
      top = y;
    if (y > bottom)
      bottom = y;

    // CURRENTLY DODGING THE PROBLEM OF DELTA_VERTICES BY SETTING IT TO 0
    updateSketch(&point_sketch, (Vector2){x, y});
  }
  printf("top: %f, bottom: %f, left: %f, right %f\n", top, bottom, left, right);

  Vector2 sketch_centroid = {0.5f * (left + right), 0.5f * (top + bottom)};
  Vector2 screen_centroid = {
      0.0f * SCREEN_WIDTH,
      0.0f * SCREEN_HEIGHT}; // {0.5f * SCREEN_WIDTH, 0.5f * SCREEN_HEIGHT};  //
                             // THIS DEPENDS ON THE CAMERA

  float sketch_height = fabsf(bottom - top), sketch_width = fabsf(right - left);

  Vector2 scale_ratios = {SCREEN_WIDTH / sketch_width,
                          SCREEN_HEIGHT / sketch_height};
  printf("scale_ratios.x: %f; scale_ratios.y %f\n", scale_ratios.x,
         scale_ratios.y);

  float final_scale;
  if (scale_ratios.x <= scale_ratios.y)
    final_scale = scale_ratios.x;
  else
    final_scale = scale_ratios.y;

  for (int i = 0; i < point_sketch.index + 1; i++) {
    Vector2 point = point_sketch.vertices[i];
    point_sketch.vertices[i] = Vector2Add(
        screen_centroid,
        Vector2Scale(Vector2Subtract(point, sketch_centroid), final_scale));
  }

  // logging info
  printf("number of points: %d\n", numVertices);

  // CAREFUL: because using `sketch` structure, when the number of points exceed
  // MAX_VERTICES then it cycles to restarts
  if (numVertices > MAX_VERTICES)
    printf("WARNING: number of points in the drawing exceed `MAX_VERTICES`, "
           "drawing may be an unexpected chunk of the drawing\n");

  printf("\n");

  fclose(file); // Close the file
  return point_sketch;
}
