#include "raylib.h"
#include <stdio.h>
#include "game.h"
#include "stdlib.h"
void SaveLevel(int levelNumber, Level *level) {    

    char filename[32];
    snprintf(filename, sizeof(filename), "levels/level_%d.bin", levelNumber);

    FILE *file = fopen(filename, "wb");
    fwrite(level, sizeof(Level), 1, file);
    fclose(file);
}

void CreateGuns(GunArray *gunArray, int arenaCenterSize) {
    gunArray->guns = (Gun*)malloc(gunArray->numberOfGunsPerSide*4 * sizeof(Gun));

    int x, y, gunSide;
    
    for (int side=0; side<4; side++) {
        for (int i=0; i<gunArray->numberOfGunsPerSide; i++) {
            if (side == 0) {
                gunSide = LEFT;
                x = gunArray->gunAreaSize/2 + gunArray->gunOffset*gunArray->gunAreaSize;
                y = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
            } else if (side == 1) {
                gunSide = RIGHT;
                x = gunArray->gunAreaSize*1.5f + arenaCenterSize - gunArray->gunOffset*gunArray->gunAreaSize;
                y = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
            } else if (side == 2) {
                gunSide = TOP;
                x = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
                y = gunArray->gunAreaSize/2 + gunArray->gunOffset*gunArray->gunAreaSize;
            } else {
                gunSide = BOTTOM;
                x = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
                y = gunArray->gunAreaSize*1.5f + arenaCenterSize - gunArray->gunOffset*gunArray->gunAreaSize;
            }
            
            gunArray->guns[side*gunArray->numberOfGunsPerSide + i] = (Gun){x, y, gunSide};
        }
    }
}

Level LoadLevel(int levelNumber, Game *game) {
    Level level;
    char filename[32];
    snprintf(filename, sizeof(filename), "levels/level_%d.bin", levelNumber);

    FILE *file = fopen(filename, "rb");
    fread(&level, sizeof(Level), 1, file);
    fclose(file);

    level.arena.gunArray.gunAreaSize *= (float)game->size;

    level.arena.center = (Rectangle){
        level.arena.gunArray.gunAreaSize, 
        level.arena.gunArray.gunAreaSize, 
        game->size - 2*level.arena.gunArray.gunAreaSize, 
        game->size - 2*level.arena.gunArray.gunAreaSize
        };

    level.player.hitbox.x = game->size/2;
    level.player.hitbox.y = game->size/2;

    level.player.hitbox.width *= (float)game->size;
    level.player.hitbox.height *= (float)game->size;
        
    CreateGuns(&level.arena.gunArray, level.arena.center.width);

    level.arena.bulletArray.bullets = (Bullet*)malloc(0);

    return level;
}