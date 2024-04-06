//
// Created by Vishal Paudel on 03/04/24.
//

#include "../include/cycloid.h"
#include "stdio.h"

struct Cycloid createCycloid(int numCycles)
{
    printf("allocating cycloid...\n");

    struct Cycloid newCycloid;

    newCycloid.numCycles = numCycles;

    newCycloid.radius = (double *) calloc(numCycles, sizeof(double));
    newCycloid.thetas = (double *) calloc(numCycles, sizeof(double));
    newCycloid.omegas = (int *) calloc(numCycles, sizeof(double));

    printf("allocated cycloid...\n");

    return newCycloid;
}

bool freeCycloid(struct Cycloid *cycloid)
{
    printf("deallocating cycloid...\n");

    free(cycloid->radius); cycloid->radius = NULL;
    free(cycloid->thetas); cycloid->thetas = NULL;
    free(cycloid->omegas); cycloid->omegas = NULL;

    printf("deallocated cycloid...\n");

    return true;
}

//int main() {
//    int N = 100;
//    struct Cycloid myCycloid;
//
//    myCycloid = createCycloid(N);
//    freeCycloid(&myCycloid);
//
//    return 0;
//}