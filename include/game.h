#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "main_menu.h"

extern int windowWidth;
extern int windowHeight;
extern int gameState;
extern int gameSize;
extern char gameName[11];
extern float deltaTime;
extern Font gameFont;

enum State {
    MAIN_MENU,
    LOADING,
    IN_GAME
};

typedef struct Game {
    bool fullscreen;
    int offsetX;
    int offsetY;
    Camera2D camera;
    Level level;
    Texture2D backgroundTexture;
    MainMenu mainMenu;
} Game;

void UpdateGame(Game *game);
void DrawGame(Game *game);
void InitializeGame(Game *game);
#endif