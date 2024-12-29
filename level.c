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

    level.player.speed *= game->size;
    level.player.hitbox.x = game->size/2;
    level.player.hitbox.y = game->size/2;

    level.player.hitbox.width *= (float)game->size;
    level.player.hitbox.height *= (float)game->size;
        
    CreateGuns(&level.arena.gunArray, level.arena.center.width);

    level.arena.bulletArray.bullets = (Bullet*)malloc(0);
    level.arena.bulletArray.bulletSpeed *= game->size;
    
    return level;
}