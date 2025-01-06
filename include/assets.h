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
} Assets;

void LoadLevelAssets(Level *level);
void LoadGameAssets(Game *game);
#endif