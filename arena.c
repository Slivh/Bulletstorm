#include "raylib.h"
#include "game.h"

void DrawArena(Arena *arena, int gameSize) {
    DrawTexturePro(
        arena->backgroundTexture, 
        (Rectangle) {0, 0, arena->backgroundTexture.width, arena->backgroundTexture.height}, 
        (Rectangle){0, 0, gameSize, gameSize},
        (Vector2) {0}, 
        0, 
        WHITE
    );
    // DrawRectangleLinesEx(arena->center, 2.0f, GREEN);
}