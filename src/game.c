#include "raylib.h"
#include "game.h"
#include "level.h"
#include <string.h>
#include "stdio.h"
#include "main_menu.h"

void InitializeGame(Game *game)
{

#if defined(PLATFORM_DESKTOP)
    platform = DESKTOP;
#elif defined(PLATFORM_ANDROID)
    platform = WEB;
#elif defined(PLATFORM_WEB)
    platform = ANDROID;
#endif

    gameState = MAIN_MENU;

    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    InitWindow(0, 0, gameName);

    windowWidth = GetMonitorWidth(GetCurrentMonitor());
    windowHeight = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(windowWidth, windowHeight);

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    if (windowWidth < windowHeight)
    {
        gameSize = windowWidth;
        game->offsetY = (windowHeight - gameSize) / 2;
        game->offsetX = 0;
    }
    else
    {
        gameSize = windowHeight;
        game->offsetX = (windowWidth - gameSize) / 2;
        game->offsetY = 0;
    }

    game->camera.target = (Vector2){0};
    game->camera.offset = (Vector2){game->offsetX, game->offsetY};
    game->camera.zoom = 1.0f;

    LoadGameAssets(game);
}

void UpdateGame(Game *game)
{

    deltaTime = GetFrameTime();

    if (gameState == IN_GAME)
    {

        UpdateLevel(&game->level);
    }
    else if (gameState == MAIN_MENU)
    {
        UpdateMainMenu(game);
    }
}

void DrawGame(Game *game)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (gameState == IN_GAME)
    {
        BeginMode2D(game->camera);
        BeginScissorMode(game->offsetX, game->offsetY, gameSize, gameSize);

        DrawLevel(&game->level);

        EndScissorMode();
        EndMode2D();
    }
    else if (gameState == MAIN_MENU)
    {
        DrawMainMenu(game);
    }

    EndDrawing();
}
