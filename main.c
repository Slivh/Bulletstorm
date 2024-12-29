#include "raylib.h"
#include "game.h"

#define PLAYER_SPEED 3.0f

int main() {
    Game game;

    game.windowWidth = 1600;
    game.windowHeight = 1400;
    
    InitWindow(game.windowWidth, game.windowHeight, "very good game");
    
    if (game.windowWidth < game.windowHeight) {
        game.size = game.windowWidth;
        game.offsetY = (game.windowHeight - game.size) / 2;
        game.offsetX = 0;
    } else {
        game.size = game.windowHeight;
        game.offsetX = (game.windowWidth - game.size) / 2;
        game.offsetY = 0;
    }

    game.camera.target = (Vector2){0};
    game.camera.offset = (Vector2){game.offsetX, game.offsetY};
    game.camera.zoom = 1.0f;  

    CreateLevel(3);
    
    game.level = LoadLevel(3, &game);

    LoadTextures(&game.level);

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        UpdatePlayer(&game.level.player, &game.level.arena, deltaTime);

        ShootGuns(&game.level.arena.gunArray, &game.level.arena.bulletArray, deltaTime);

        UpdateBullets(&game.level.arena.bulletArray);

        BeginDrawing();
        BeginMode2D(game.camera);
        BeginScissorMode(game.offsetX, game.offsetY, game.size, game.size);
            
            DrawArena(&game.level.arena, game.size);

            DrawPlayer(&game.level.player);

            DrawBullets(&game.level.arena.bulletArray);

            DrawGuns(&game.level.arena.gunArray);
            
        EndScissorMode();
        EndMode2D();
        EndDrawing();

    }
    CloseWindow();

    return 0;
}