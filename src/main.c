#include "raylib.h"
#include <stdio.h>
#include "level.h"
#include "game.h"
#include "main_menu.h"
#include <string.h>
#include <setjmp.h>

int windowWidth;
int windowHeight;
int gameState;
int gameSize;
char* gameName = "Bulletstorm";
float deltaTime = 0;
Font gameFont;
jmp_buf buf;

int main()
{
    Game game;

    InitializeGame(&game);

    CreateLevel(0);
    CreateLevel(1);
    CreateLevel(2);
    CreateLevel(3);

    InitializeMainMenu(&game);

    if (setjmp(buf))
        CloseWindow();

    while (!WindowShouldClose())
    {
        UpdateGame(&game);

        DrawGame(&game);
    }

    CloseWindow();

    return 0;
}