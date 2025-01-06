#include "raylib.h"
#include "assets.h"
#include "level.h"
#include "game.h"
#include <stdio.h>

void LoadLevelAssets(Level *level)
{
    level->arena.backgroundTexture = LoadTexture(level->assets.backgroundTexturePath);
    level->arena.gunArray.gunTexture = LoadTexture(level->assets.gunTexturePath);
    level->player.playerTexture = LoadTexture(level->assets.playerTexturePath);
    level->arena.bulletArray.bulletTexture = LoadTexture(level->assets.bulletTexturePath);
    level->arena.explosionArray.explosionTexture = LoadTexture(level->assets.explosionTexturePath);
}

void LoadGameAssets(Game *game)
{
    gameFont = LoadFont("assets/fonts/alagard.png");
}
