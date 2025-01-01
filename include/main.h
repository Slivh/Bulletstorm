#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include "level.h"

typedef struct Game {
    bool fullscreen;
    int size;
    int offsetX;
    int offsetY;
    int windowWidth;
    int windowHeight;
    Camera2D camera;
    Level level;
} Game;

#endif