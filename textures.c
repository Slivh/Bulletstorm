#include "raylib.h"
#include "game.h"

void LoadTextures(Level *level) {
    level->arena.backgroundTexture = LoadTexture(level->textures.backgroundTexturePath);
    level->arena.gunArray.gunTexture = LoadTexture(level->textures.gunTexturePath);
    level->player.playerTexture = LoadTexture(level->textures.playerTexturePath);
    level->arena.bulletArray.bulletTexture = LoadTexture(level->textures.bulletTexturePath);
    level->arena.explosionArray.explosionTexture = LoadTexture(level->textures.explosionTexturePath);
    level->font = LoadFont("resources/fonts/alagard.png");
}

