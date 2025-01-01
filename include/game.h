#ifndef GAME_H
#define GAME_H

#include "level.h"

enum State {
    TITLE_SCREEN,
    LOADING,
    IN_GAME
};

typedef struct Game {
    bool fullscreen;
    int size;
    int offsetX;
    int offsetY;
    int windowWidth;
    int windowHeight;
    Camera2D camera;
    Level level;
    Font font;
    char name[16];
    int state;
} Game;

void UpdateGame(Game *game);
void DrawGame(Game *game);
void InitializeGame(Game *game);
#endif