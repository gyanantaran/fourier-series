// sketch.c
// author: vishalpaudel
// 2024-04-04
// Note: A data structure wrapper for a bunch of Vector2 with an index

#include "../include/sketch.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#include "raymath.h"

#include "../include/constants.h"


struct Sketch createSketch() {
    printf("allocating sketch...\n");
    struct Sketch sketch;
    sketch.vertices = calloc(MAX_VERTICES, sizeof(Vector2));
    sketch.index = -1;
    sketch.connectFirstLast = false;

    printf("...allocated sketch\n");

    return sketch;
}

bool freeSketch(struct Sketch *sketch) {
    printf("deallocating sketch...\n");
    free(sketch->vertices);
    sketch->vertices = NULL;
    printf("...deallocated sketch\n");

    return true;
}

void drawSketch(struct Sketch *sketch, Color color) {
    if (sketch->index > 0) {

        DrawLineStrip(sketch->vertices, sketch->index + 1, color);

        // connect first and last point
        if (sketch->connectFirstLast) {
            if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
                Vector2 firstPoint = sketch->vertices[0], latestPoint = sketch->vertices[sketch->index];
                DrawLineV(firstPoint, latestPoint, color);
            }
        }
    }

    if (IsKeyPressed(KEY_E)) {
        sketch->index = -1;
        ClearBackground(BACKGROUND_COLOR);
    }
}

void updateSketch(struct Sketch *sketch, Vector2 newPoint) {
    if (sketch->index < 0) {
        sketch->index = 0;
        sketch->vertices[sketch->index] = newPoint;
    } else {
        Vector2 lastPoint;
        lastPoint = sketch->vertices[sketch->index];
        if (Vector2Distance(newPoint, lastPoint) > DELTA_VERTICES) {
            sketch->index = (sketch->index + 1) % MAX_VERTICES;
            sketch->vertices[sketch->index] = newPoint;
        }
    }
}

//int main(void)
//{
//    struct Sketch sketch;
//    sketch = createSketch();
//    freeSketch(&sketch);
//
//    return 0;
//}
