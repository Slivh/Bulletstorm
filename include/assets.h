#ifndef ASSETS_H
#define ASSETS_H

typedef struct Level Level;
typedef struct Game Game;

typedef struct Assets
{
    char gunTexturePath[64];
    char backgroundTexturePath[64];
    char playerTexturePath[64];
    char bulletTexturePath[64];
    char explosionTexturePath[64];
    char heartFullTexturePath[64];
    char heartEmptyTexturePath[64];

    char levelMusicPath[64];
    char mainMenuMusicPath[64];
    char deathScreenMusicPath[64];

    char explosionSoundPath[64];
    char deathSoundPath[64];
    char firingSoundPath[64];
} Assets;

void LoadLevelAssets(Level *level);
void LoadGameAssets(Game *game);
void UnloadLevelAssets(Level *level);

#endif