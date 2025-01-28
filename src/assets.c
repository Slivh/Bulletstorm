#include "raylib.h"
#include "assets.h"
#include "level.h"
#include "game.h"
#include <stdio.h>

void LoadLevelAssets(Level *level)
{
    level->arena.backgroundTexture = LoadTexture(level->assets.backgroundTexturePath);
    level->arena.gunArray.gunTexture = LoadTexture(level->assets.gunTexturePath);
    level->arena.bulletArray.bulletTexture = LoadTexture(level->assets.bulletTexturePath);
    level->arena.explosionArray.explosionTexture = LoadTexture(level->assets.explosionTexturePath);
    level->player.playerTexture = LoadTexture(level->assets.playerTexturePath);
    level->player.heartFullTexture = LoadTexture(level->assets.heartFullTexturePath);
    level->player.heartEmptyTexture = LoadTexture(level->assets.heartEmptyTexturePath);

    level->music = LoadMusicStream(level->assets.levelMusicPath);
    level->deathScreen.music = LoadMusicStream(level->assets.deathScreenMusicPath);

    level->arena.explosionArray.explosionSound = LoadSound(level->assets.explosionSoundPath);
    level->arena.gunArray.firingSound = LoadSound(level->assets.firingSoundPath);
    level->player.deathSound = LoadSound(level->assets.deathSoundPath);
}

void LoadGameAssets(Game *game)
{
    gameFont = LoadFont("assets/fonts/alagard.png");
    game->mainMenu.music = LoadMusicStream("assets/audio/music/main_menu.mp3");
}

void UnloadLevelAssets(Level *level)
{
    UnloadTexture(level->arena.backgroundTexture);
    UnloadTexture(level->arena.gunArray.gunTexture);
    UnloadTexture(level->arena.bulletArray.bulletTexture);
    UnloadTexture(level->arena.explosionArray.explosionTexture);
    UnloadTexture(level->player.playerTexture);
    UnloadTexture(level->player.heartFullTexture);
    UnloadTexture(level->player.heartEmptyTexture);

    UnloadMusicStream(level->music);

    UnloadSound(level->arena.explosionArray.explosionSound);
}