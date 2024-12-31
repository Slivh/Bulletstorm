#include "raylib.h"
#include <string.h>
#include "game.h"

void CreateLevel(int levelNumber) {
    Level level;

    strcpy(level.textures.backgroundTexturePath, "resources/textures/arena/maps/autumn.png");

    level.timer = 0;
    
    level.arena.gunArray.isGunRotated = true;
    level.arena.gunArray.numberOfGunsPerSide = 10;
    level.arena.gunArray.gunAreaSize = 0.15f;
    level.arena.gunArray.gunTextureOffset = 0.0f;
    level.arena.gunArray.gunOffset = 0.1f;
    level.arena.gunArray.gunScaling = 0.5f;
    level.arena.gunArray.gunFireDelay = 5;
    level.arena.gunArray.gunFireDelayDeviation = 4;
    level.arena.gunArray.gunFireAngleDeviation = 40;
    strcpy(level.textures.gunTexturePath, "resources/textures/arena/guns/lasergun.png");

    level.arena.bulletArray.bulletSize = (Vector2){0.025f, 0.013f};
    level.arena.bulletArray.bulletSpeed = 0.3f;
    level.arena.bulletArray.size = 0;
    level.arena.bulletArray.logicalSize = 0;
    strcpy(level.textures.bulletTexturePath, "resources/textures/arena/guns/fireball.png");

    level.arena.explosionArray.animationSpeed = 0.2f;
    level.arena.explosionArray.explosionSize = (Vector2){0.025f, 0.025f};
    level.arena.explosionArray.size = 0;
    level.arena.explosionArray.logicalSize = 0;
    strcpy(level.textures.explosionTexturePath, "resources/textures/arena/guns/explosion.png");



    level.player.lives = 3;
    level.player.invulnerability = 0;
    level.player.hitbox = (Rectangle){0, 0, 0.032, 0.048f};
    level.player.currentFrame = 0;
    level.player.timeSinceLastUpdate = 0;
    level.player.animationSpeed = 0.1f;
    level.player.textureOffset = (Vector2){-0.009f, -0.012f};
    level.player.textureRec = (Rectangle){0, 0, 0.048f, 0.072f};
    level.player.speed = 0.4f;
    level.player.timeSinceDeath = 0;
    level.player.color = WHITE;
    strcpy(level.textures.playerTexturePath, "resources/textures/player/orange.png");
    
    SaveLevel(levelNumber, &level);
}   