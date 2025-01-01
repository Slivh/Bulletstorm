#include "raylib.h"
#include "title_screen.h"
#include "game.h"
#include <stdio.h>

void DrawTitleScreen(Game *game) {
    ClearBackground(GREEN);
    float fontSize = 0.05f*(float)game->size;
    float spacing = 0.12*fontSize;

    Vector2 textSize = MeasureTextEx(game->font, game->name, fontSize, spacing);
    Vector2 textPosition = {game->size/2 - textSize.x/2, game->size/4 - textSize.y/2};
    DrawTextEx(game->font, game->name, textPosition, fontSize, spacing, RAYWHITE);
}

void UpdateTitleScreen(Game *game) {
    if (IsKeyDown(KEY_ENTER)) {
        game->state = IN_GAME;
        game->level = LoadLevel(1, game);
    }
}