#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "main_menu.h"
#include "difficulty_menu.h"
#include <setjmp.h>

extern int windowWidth;
extern int windowHeight;
extern int gameState;
extern int gameSize;
extern char* gameName;
extern float deltaTime;
extern Font gameFont;
extern jmp_buf buf; 

enum State
{
    MAIN_MENU,
    IN_GAME,
    DIFFICULTY_MENU
};

typedef struct Game
{
    bool fullscreen;
    int offsetX;
    int offsetY;
    Camera2D camera;
    Level level;
    Texture2D backgroundTexture;
    MainMenu mainMenu;
    DifficultyMenu difficultyMenu;
} Game;

void UpdateGame(Game *game);
void DrawGame(Game *game);
void InitializeGame(Game *game);
#endif