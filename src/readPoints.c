// readPoints.c

#include "../include/readPoints.h"

#include "math.h"

struct Drawing readPointsFile(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    } else {
        printf("Reading the points-file!\n");
    }
    int numSketches;
    fscanf(file, "%d", &numSketches); // Read the number of sections
    printf("The number of paths: %d\n", numSketches);

    struct Drawing drawing = createDrawing(numSketches);
    float left = -1 * INFINITY, right = INFINITY, top = -1 * INFINITY, bottom = INFINITY;
    for (int i = 0; i < numSketches; i++) {
        int numVertices;
        fscanf(file, "%d", &numVertices); // Read the number of rows in the current section

        for (int j = 0; j < numVertices; j++) {
            float x, y;
            fscanf(file, "%f %f", &x, &y); // Read two numbers from the current row

            // CURRENTLY DODGING THE PROBLEM OF DELTA_VERTICES BY SETTING IT TO 0
            updateSketch(&drawing.sketches[i], (Vector2) {x, y});
        }

        // logging info
        printf("Path %d:\n", i + 1);
        printf("number of points: %d\n", numVertices);

        // CAREFUL: because using `sketch` structure, when the number of points exceed MAX_VERTICES then it cycles to restarts
        if (numVertices > MAX_VERTICES)
            printf("WARNING: number of points in the drawing exceed `MAX_VERTICES`, drawing may be an unexpected chunk of the drawing\n");

        printf("\n");
    }
    fclose(file); // Close the file
    return drawing;
}