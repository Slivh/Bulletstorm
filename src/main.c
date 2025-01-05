#include "raylib.h"
#include <stdio.h>
#include "level.h"
#include "game.h"
#include "main_menu.h"
#include <string.h>

int windowWidth = 2560;
int windowHeight = 1600;
int gameState = MAIN_MENU;
int gameSize = 0;
char gameName[11] = "Bulletstorm";
float deltaTime = 0;
Font gameFont;

int main() {
    Game game;

    InitializeGame(&game);

    CreateLevel(1);

    InitializeMainMenu(&game);

    while (!WindowShouldClose()) {
        
        UpdateGame(&game);

        DrawGame(&game);

    }
    CloseWindow();

    return 0;
}