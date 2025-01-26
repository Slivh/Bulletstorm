#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "buttons.h"

typedef struct Game Game;

typedef struct MainMenu
{
    Buttons buttons;
    float titleFontSize;
    float titleSpacing;
    Vector2 titlePosition;
    Music music;
} MainMenu;

void InitializeMainMenu(Game *game);
void UpdateMainMenu(Game *game);
void DrawMainMenu(Game *game);

#endif