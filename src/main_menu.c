#include "main_menu.h"
#include "raylib.h"
#include "game.h"
#include "buttons.h"
#include "stdio.h"
#include <string.h>
#include "death_screen.h"

void InitializeMainMenu(Game *game)
{
    MainMenu *mainMenu = &game->mainMenu;
    mainMenu->buttons.count = 3;
    mainMenu->buttons.margin = 0.02f * gameSize;
    mainMenu->buttons.fontSize = 0.05f * gameSize;
    strcpy(mainMenu->buttons.names[0], "Play");
    strcpy(mainMenu->buttons.names[1], "Settings");
    strcpy(mainMenu->buttons.names[2], "Exit");
    mainMenu->buttons.selected = 0;

    mainMenu->titleFontSize = 0.15f * (float)gameSize;
    mainMenu->titleSpacing = 0.06 * mainMenu->titleFontSize;

    Vector2 titleSize = MeasureTextEx(gameFont, gameName, mainMenu->titleFontSize, mainMenu->titleSpacing);
    mainMenu->titlePosition = (Vector2){windowWidth / 2 - titleSize.x / 2, windowHeight / 4 - titleSize.y / 2};
}

void UpdateMainMenu(Game *game)
{
    MainMenu *mainMenu = &game->mainMenu;

    // Update selected button
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && mainMenu->buttons.selected < mainMenu->buttons.count - 1)
        mainMenu->buttons.selected += 1;
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && mainMenu->buttons.selected > 0)
        mainMenu->buttons.selected -= 1;

    // Update game state if button is pressed
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        if (mainMenu->buttons.selected == 0)
        {
            gameState = DIFFICULTY_MENU;
            InitializeDifficultyMenu(&game->difficultyMenu);
            // game->level = LoadLevel(1);
        }
        else if (mainMenu->buttons.selected == 1)
        {
        }
        else if (mainMenu->buttons.selected == 2)
        {
            CloseWindow();
        }
    }
}

void DrawMainMenu(Game *game)
{
    MainMenu *mainMenu = &game->mainMenu;

    // Draw game title
    DrawTextEx(gameFont, gameName, mainMenu->titlePosition, mainMenu->titleFontSize, mainMenu->titleSpacing, RAYWHITE);

    // Draw buttons
    Color color;
    for (int i = 0; i < mainMenu->buttons.count; i++)
    {
        color = (mainMenu->buttons.selected == i) ? deathRed : RAYWHITE;

        Vector2 textSize = MeasureTextEx(gameFont, mainMenu->buttons.names[i], mainMenu->buttons.fontSize, 0.06f * mainMenu->buttons.fontSize);
        // DrawRectangle(windowWidth/2 - textSize.x/2, windowHeight/2 + textSize.y * i + mainMenu->buttons.margin * i, textSize.x, textSize.y, RED);
        Vector2 textPosition = {windowWidth / 2 - textSize.x / 2, windowHeight / 2 + textSize.y * i + mainMenu->buttons.margin * i};
        DrawTextEx(gameFont, mainMenu->buttons.names[i], textPosition, mainMenu->buttons.fontSize, 0.06f * mainMenu->buttons.fontSize, color);
    }
}