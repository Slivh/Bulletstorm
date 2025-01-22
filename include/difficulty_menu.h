#ifndef DIFFICULTY_MENU_H
#define DIFFICULTY_MENU_H

#include "buttons.h"

typedef struct Game Game;

typedef struct DifficultyMenu
{
    Buttons buttons;
    char instruction[32];
    float instructionFontSize;
    float instructionSpacing;
    Vector2 instructionSize;
    Vector2 instructionPosition;
} DifficultyMenu;

void InitializeDifficultyMenu(DifficultyMenu *difficultyMenu);
void UpdateDifficultyMenu(Game *game);
void DrawDifficultyMenu(DifficultyMenu *difficultyMenu);

#endif