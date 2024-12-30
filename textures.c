#include "raylib.h"
#include "game.h"

void LoadTextures(Level *level) {
    level->arena.backgroundTexture = LoadTexture(level->textures.backgroundTexturePath);
    level->arena.gunArray.gunTexture = LoadTexture(level->textures.gunTexturePath);
    level->player.playerTexture = LoadTexture(level->textures.gunTexturePath);
    level->arena.bulletArray.bulletTexture = LoadTexture(level->textures.bulletTexturePath);
    level->alagard = LoadFont("resources/alagard.png");
}

