#include "raylib.h"
#include <string.h>
#include "game.h"
void CreateLevel(int levelNumber) {
    Level level;

    strcpy(level.textures.backgroundTexturePath, "resources/winter.png");

    level.arena.gunArray.isGunRotated = false;
    level.arena.gunArray.numberOfGunsPerSide = 8;
    level.arena.gunArray.gunAreaSize = 0.15f;
    level.arena.gunArray.gunTextureOffset = 0.0f;
    level.arena.gunArray.gunOffset = 0.1f;
    level.arena.gunArray.gunScaling = 0.5f;
    level.arena.gunArray.gunFireDelay = 7;
    level.arena.gunArray.gunFireDelayDeviation = 7;
    level.arena.gunArray.gunFireAngleDeviation = 20;
    strcpy(level.textures.gunTexturePath, "resources/lasergun.png");

    level.arena.bulletArray.bulletSize = (Vector2){30, 15};
    level.arena.bulletArray.bulletSpeed = 0.3f;
    level.arena.bulletArray.size = 0;
    level.arena.bulletArray.logicalSize = 0;
    strcpy(level.textures.bulletTexturePath, "resources/fireball.png");


    level.player.lives = 3;
    level.player.invulnerability = 0;
    level.player.hitbox = (Rectangle){0, 0, 0.04f, 0.04f};
    level.player.speed = 0.4f;
    strcpy(level.textures.playerTexturePath, "resources/player.png");
    
    SaveLevel(levelNumber, &level);
}   