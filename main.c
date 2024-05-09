// main.c
// author: vishalpaudel

#include "raylib.h"
#include "include/sketch.h"
#include "include/cycloid.h"
#include "include/fourier.h"
#include "include/readPoints.h"

struct GameState {
    bool sketchingFinished;
    bool cameraZoomed;

    bool showAllHarmonics;

    bool addHarmonicSignal;
    bool removeHarmonicSignal;

    bool updateFourierSignal;
    bool eraseEverythingSignal;
};

struct GameObjects {
    struct Sketch signal;
    struct Cycloid cycloid;

    Camera2D camera;
};

void initApp();

void deInitApp(struct GameObjects *objects);

void handle_events(struct GameState *state);

void update(const struct GameState *state, struct GameObjects *objects);

void draw(const struct GameState *state, struct GameObjects *objects);

//    Camera2D camera =

int main(void) {
    initApp();

    Vector2 window_offset = (Vector2) {(float) GetScreenWidth() / 2.0f, (float) GetScreenHeight() / 2.0f};
    struct GameState state = {.sketchingFinished=true, .cameraZoomed=false, .showAllHarmonics=false, .eraseEverythingSignal=false};
    struct GameObjects objects = {
            .signal=readPointsFile(POINTS_FILE_PATH),
            .cycloid=createCycloid(5, (Vector2) {0, 0}),
            .camera={
                    .target = {0, 0}, .offset = window_offset, .rotation = 0, .zoom = 1.0f
            }
    };
    objects.signal.connectFirstLast = true;
    updateFourier(&objects.cycloid, &objects.signal);

    while (!WindowShouldClose()) {
        handle_events(&state);
        update(&state, &objects);
        draw(&state, &objects);
    }
    deInitApp(&objects);
    return 0;
}

void update(const struct GameState *state, struct GameObjects *objects) {
    if (!state->sketchingFinished) {
        Vector2 mouse_pos = GetMousePosition();
        mouse_pos = GetScreenToWorld2D(mouse_pos, objects->camera);
        updateSketch(&objects->signal, mouse_pos);
    } else if (state->updateFourierSignal) {
        printf("Hello\n");
        updateFourier(&objects->cycloid, &objects->signal);
    }
    else { updateCycloid(&objects->cycloid); }

    if (state->addHarmonicSignal) { objects->cycloid.numCycles += 1; }
    if (state->removeHarmonicSignal) { objects->cycloid.numCycles -= 1; }
}

void draw(const struct GameState *state, struct GameObjects *objects) {
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    DrawText(TextFormat("Number of Cycloids: %d\n\n\n\nPress E to Erase\n\nPress SPACE to zoom-in/zoom-out",
                        objects->cycloid.numCycles), (int) (0.075 * GetScreenWidth()),
             (int) (0.075 * GetScreenHeight()), 20, PEN_COLOR);
    DrawText(TextFormat(
                     "Fourier Series Project\n\nSignals and Systems\n\nVishal Paudel\n\nunder the guidance of \n\nProfessor Vivek Deulkar"),
             (int) (0.75 * GetScreenWidth()), (int) (0.8 * GetScreenHeight()), 20, TEXT_COLOR);

    BeginMode2D(objects->camera);
    drawSketch(&objects->signal, PEN_COLOR);
    if (state->sketchingFinished) drawCycloid(&objects->cycloid);
    EndMode2D();
    EndDrawing();
}

void initApp() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "fourier-series");
    SetTargetFPS(MAX_FPS);
}

void deInitApp(struct GameObjects *objects) {
    freeSketch(&objects->signal);
    freeCycloid(&objects->cycloid);
    CloseWindow();
}

void handle_events(struct GameState *state) {
    // jugaad to get an impulse of add/remove harmonic signal
    state->addHarmonicSignal = false;
    state->removeHarmonicSignal = false;

    state->updateFourierSignal = false;
    state->eraseEverythingSignal = false;

    if (false) {

    } else if (IsKeyPressed(KEY_E)) { printf("Pressed E\n");
        state->eraseEverythingSignal = true;
    } else if (IsKeyReleased(KEY_E)) { printf("Released E\n");
    } else if (IsKeyPressed(KEY_SPACE)) { printf("Pressed SPACE\n");
        state->cameraZoomed = !(state->cameraZoomed);
    } else if (IsKeyPressed(KEY_A)) { printf("Pressed A\n");
        state->addHarmonicSignal = true;
        state->updateFourierSignal = true;
    } else if (IsKeyPressed(KEY_D)) { printf("Pressed D\n");
        state->removeHarmonicSignal = true;
    } else if (IsKeyPressed(KEY_S)) { printf("Pressed S\n");
    } else if (IsKeyPressed(KEY_W)) { printf("Pressed W\n");
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { printf("Mouse Left Pressed\n");
        state->sketchingFinished = false;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { printf("Mouse Left Released\n");
        state->sketchingFinished = true;
        state->updateFourierSignal = true;
    }
}