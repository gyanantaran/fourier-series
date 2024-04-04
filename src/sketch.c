//
// Created by Vishal Paudel on 04/04/24.
//

#include "../include/sketch.h"

#include "raylib.h"

#include "stdlib.h"
#include "stdio.h"

const int MAX_VERTICES = 1000;

struct Sketch createSketch()
{
    printf("allocating sketch...\n");
    struct Sketch sketch;
    sketch.vertices = calloc(MAX_VERTICES, sizeof(Vector2));
    sketch.index    = -1;
    printf("allocated sketch...\n");

    return sketch;
}

bool freeSketch(struct Sketch * sketch)
{
    printf("deallocating sketch...\n");
    free(sketch->vertices); sketch->vertices = NULL;
    printf("deallocated sketch...\n");

    return true;
}

//int main(void)
//{
//    struct Sketch mySketch;
//    mySketch = createSketch();
//    freeSketch(&mySketch);
//
//    return 0;
//}