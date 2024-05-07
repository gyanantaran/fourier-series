// drawing.c
// author: vishalpaudel
// date: 2024-04-11
// note: drawing is a collection of `sketch`(es)

#include "../include/drawing.h"

#include "stdio.h"
#include "stdlib.h"

struct Drawing createDrawing(int numSketches) {
    printf("Allocating array of sketches...\n");
    struct Drawing drawing;
    drawing.numSketches = numSketches;
    drawing.sketches = (struct Sketch *) calloc(sizeof(struct Sketch), numSketches);
    for (int i = 0; i < numSketches; i++) { drawing.sketches[i] = createSketch(); }
    printf("...Allocated array of sketches\n");

    return drawing;
}

bool freeDrawing(struct Drawing *drawing) {
    printf("Deallocating drawing...\n");
    for (int i = 0; i < drawing->numSketches; i++) freeSketch(&drawing->sketches[i]);
    free(drawing->sketches);
    printf("...Deallocated drawing\n");
    return true;
}
