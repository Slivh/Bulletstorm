#include "raylib.h"
#include "game.h"
#include <stdio.h>

#define PLAYER_SPEED 3.0f

int main() {
    Game game;

    game.windowWidth = 1400;
    game.windowHeight = 1400;
    
    InitWindow(game.windowWidth, game.windowHeight, "Bulletstorm");
    
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

        if (game.level.player.lives > 0) {
            UpdatePlayer(&game.level.player, &game.level.arena, deltaTime);

            ShootGuns(&game.level.arena.gunArray, &game.level.arena.bulletArray, deltaTime);

            UpdateBullets(&game.level.arena.bulletArray, game.level.arena.center, deltaTime);
        }

        BeginDrawing();
        BeginMode2D(game.camera);
        BeginScissorMode(game.offsetX, game.offsetY, game.size, game.size);

            DrawArena(&game.level.arena, game.size);

            DrawPlayer(&game.level.player);

            DrawBullets(&game.level.arena.bulletArray);

            DrawGuns(&game.level.arena.gunArray);
            
            // DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), 0, 0, 40, RED);

            if (game.level.player.lives <= 0) {

                game.level.player.timeSinceDeath += deltaTime;

                if (game.level.player.timeSinceDeath < 5) {

                    Vector2 textSize = MeasureTextEx(game.level.font, "SKILL ISSUE", 0.15f*(float)game.size, 5);
                    Vector2 textPosition = {game.size/2 - textSize.x/2, game.size/2 - textSize.y/2};
                    DrawRectangle(0, textPosition.y-0.2f*textSize.y, game.size, textSize.y*1.4f, (Color){0, 0, 0, 128});
                    DrawTextEx(game.level.font, "SKILL ISSUE", textPosition, 0.15f*(float)game.size, 5, (Color){126, 0, 7, 255});
                } else {
                    
                }
                
            } else {
                game.level.timer += deltaTime;
            }

            DrawText(TextFormat("timer: %.2fs", game.level.timer), 20, 50, 40, RED);

        EndScissorMode();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}