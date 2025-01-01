#include "raylib.h"
#include "game.h"
#include "level.h"
#include <string.h>
#include "title_screen.h"
#include "loading_screen.h"

void InitializeGame(Game *game) {

    strcpy(game->name, "Bulletstorm");

    InitWindow(game->windowWidth, game->windowHeight, game->name);
    
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    game->state = TITLE_SCREEN;
    
    if (game->windowWidth < game->windowHeight) {
        game->size = game->windowWidth;
        game->offsetY = (game->windowHeight - game->size) / 2;
        game->offsetX = 0;
    } else {
        game->size = game->windowHeight;
        game->offsetX = (game->windowWidth - game->size) / 2;
        game->offsetY = 0;
    }

    game->camera.target = (Vector2){0};
    game->camera.offset = (Vector2){game->offsetX, game->offsetY};
    game->camera.zoom = 1.0f; 

    LoadGameAssets(game); 
}

void UpdateGame(Game *game) {

    float deltaTime = GetFrameTime();

    if (game->state == TITLE_SCREEN) {

        UpdateTitleScreen(game);

    } else if (game->state == LOADING) {

    } else if (game->state == IN_GAME) {

        UpdateLevel(&game->level, deltaTime);

    }

}

void DrawGame(Game *game) {
    BeginDrawing();
    BeginMode2D(game->camera);
    BeginScissorMode(game->offsetX, game->offsetY, game->size, game->size);

        if (game->state == TITLE_SCREEN) {

            DrawTitleScreen(game);

        } else if (game->state == LOADING) {

            DrawLoadingScreen(game);

        } else if (game->state == IN_GAME) {

            DrawLevel(&game->level, game->size);

        }

    EndScissorMode();
    EndMode2D();
    EndDrawing();
}
