#include "difficulty_menu.h"
#include "raylib.h"
#include "game.h"
#include "buttons.h"
#include "stdio.h"
#include <string.h>
#include "death_screen.h"

void InitializeDifficultyMenu(DifficultyMenu *difficultyMenu)
{
    strcpy(difficultyMenu->instruction, "Select difficulty");
    difficultyMenu->instructionFontSize = 0.15f * (float)gameSize;
    difficultyMenu->instructionSpacing = 0.06f * difficultyMenu->instructionFontSize;
    difficultyMenu->instructionSize = MeasureTextEx(gameFont, difficultyMenu->instruction, difficultyMenu->instructionFontSize, difficultyMenu->instructionSpacing);
    difficultyMenu->instructionPosition = (Vector2){windowWidth / 2 - difficultyMenu->instructionSize.x / 2, windowHeight / 4 - difficultyMenu->instructionSize.y / 2};

    difficultyMenu->buttons.count = 4;
    difficultyMenu->buttons.margin = 0.02f * gameSize;
    difficultyMenu->buttons.fontSize = 0.05f * gameSize;
    strcpy(difficultyMenu->buttons.names[0], "Easy");
    strcpy(difficultyMenu->buttons.names[1], "Normal");
    strcpy(difficultyMenu->buttons.names[2], "Hard");
    strcpy(difficultyMenu->buttons.names[3], "Nightmare");
    difficultyMenu->buttons.selected = 0;
}

void UpdateDifficultyMenu(Game *game)
{
    DifficultyMenu *difficultyMenu = &game->difficultyMenu;

    UpdateMusicStream(game->mainMenu.music);

    // Update selected button
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && difficultyMenu->buttons.selected < difficultyMenu->buttons.count - 1)
        difficultyMenu->buttons.selected += 1;
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && difficultyMenu->buttons.selected > 0)
        difficultyMenu->buttons.selected -= 1;

    // Update game state if button is pressed
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        gameState = MAIN_MENU;
    }
    else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream(game->mainMenu.music);
    
        if (difficultyMenu->buttons.selected == 0)
        {
            game->level = LoadLevel(0);
        }
        else if (difficultyMenu->buttons.selected == 1)
        {
            game->level = LoadLevel(1);
        }
        else if (difficultyMenu->buttons.selected == 2)
        {
            game->level = LoadLevel(2);
        }
        else if (difficultyMenu->buttons.selected == 3)
        {
            game->level = LoadLevel(3);
        }
    }
}

void DrawDifficultyMenu(DifficultyMenu *difficultyMenu)
{

    DrawTextEx(gameFont, difficultyMenu->instruction, difficultyMenu->instructionPosition, difficultyMenu->instructionFontSize, difficultyMenu->instructionSpacing, RAYWHITE);

    Color color;
    for (int i = 0; i < difficultyMenu->buttons.count; i++)
    {
        color = (difficultyMenu->buttons.selected == i) ? deathRed : RAYWHITE;

        Vector2 textSize = MeasureTextEx(gameFont, difficultyMenu->buttons.names[i], difficultyMenu->buttons.fontSize, 0.06f * difficultyMenu->buttons.fontSize);
        Vector2 textPosition = {windowWidth / 2 - textSize.x / 2, windowHeight / 2 + textSize.y * i + difficultyMenu->buttons.margin * i};
        DrawTextEx(gameFont, difficultyMenu->buttons.names[i], textPosition, difficultyMenu->buttons.fontSize, 0.06f * difficultyMenu->buttons.fontSize, color);
    }
}
