#include "raylib.h"
#include <stdio.h>
#include "level.h"
#include "raymath.h"
#include <stdlib.h>
#include <string.h>
#include "death_screen.h"
#include "game.h"

void SaveLevel(int levelNumber, Level *level)
{

    char filename[32];
    snprintf(filename, sizeof(filename), "assets/levels/level_%d.bin", levelNumber);

    FILE *file = fopen(filename, "wb");
    fwrite(level, sizeof(Level), 1, file);
    fclose(file);
}

Level LoadLevel(int levelNumber)
{
    gameState = IN_GAME;

    Level level = {0};
    char filename[32];
    snprintf(filename, sizeof(filename), "assets/levels/level_%d.bin", levelNumber);

    FILE *file = fopen(filename, "rb");
    fread(&level, sizeof(Level), 1, file);
    fclose(file);

    level.number = levelNumber;

    level.arena.gunArray.gunAreaSize *= (float)gameSize;
    level.arena.center = (Rectangle){
        level.arena.gunArray.gunAreaSize,
        level.arena.gunArray.gunAreaSize,
        gameSize - 2 * level.arena.gunArray.gunAreaSize,
        gameSize - 2 * level.arena.gunArray.gunAreaSize};

    level.player.speed *= gameSize;
    level.player.hitbox.width *= (float)gameSize;
    level.player.hitbox.height *= (float)gameSize;
    level.player.hitbox.x = gameSize / 2 - level.player.hitbox.width / 2;
    level.player.hitbox.y = gameSize / 2 - level.player.hitbox.height / 2;

    level.player.textureOffset = Vector2Scale(level.player.textureOffset, gameSize);

    level.player.textureRec.width *= (float)gameSize;
    level.player.textureRec.height *= (float)gameSize;
    level.player.textureRec.x = level.player.hitbox.x + level.player.textureOffset.x;
    level.player.textureRec.y = level.player.hitbox.y + level.player.textureOffset.y;

    level.arena.bulletArray.bulletSize = Vector2Scale(level.arena.bulletArray.bulletSize, gameSize);

    CreateGuns(&level.arena.gunArray, level.arena.center.width);

    level.arena.bulletArray.bullets = (Bullet *)malloc(0);
    level.arena.bulletArray.bulletSpeed *= gameSize;

    level.arena.explosionArray.explosionSize = Vector2Scale(level.arena.explosionArray.explosionSize, gameSize);
    level.arena.explosionArray.explosions = (Explosion *)malloc(0);

    LoadLevelAssets(&level);

    return level;
}

void CreateLevel(int levelNumber)
{
    Level level;

    strcpy(level.assets.backgroundTexturePath, "assets/textures/arena/maps/spring.png");

    level.timer = 0;

    // Gun properties
    level.arena.gunArray.isGunRotated = true;
    level.arena.gunArray.numberOfGunsPerSide = 10;
    level.arena.gunArray.gunAreaSize = 0.15f;
    level.arena.gunArray.gunTextureOffset = 0.0f;
    level.arena.gunArray.gunOffset = 0.0f;
    level.arena.gunArray.gunScaling = 0.3f;
    level.arena.gunArray.gunFireDelay = 7;
    level.arena.gunArray.gunFireDelayDeviation = 6;
    level.arena.gunArray.gunFireAngleDeviation = 40;
    level.arena.gunArray.animationSpeed = 0.05f;
    strcpy(level.assets.gunTexturePath, "assets/textures/arena/guns/drone_new.png");

    // Bullet properties
    level.arena.bulletArray.bulletSize = (Vector2){0.025f, 0.013f};
    level.arena.bulletArray.bulletSpeed = 0.55f;
    level.arena.bulletArray.size = 0;
    level.arena.bulletArray.logicalSize = 0;
    strcpy(level.assets.bulletTexturePath, "assets/textures/arena/guns/fireball.png");

    // Explosions properties
    level.arena.explosionArray.animationSpeed = 0.05f;
    level.arena.explosionArray.explosionSize = (Vector2){0.025f, 0.025f};
    level.arena.explosionArray.size = 0;
    level.arena.explosionArray.logicalSize = 0;
    strcpy(level.assets.explosionTexturePath, "assets/textures/arena/guns/explosion.png");

    // Player properties
    level.player.isDead = false;
    level.player.lives = 3;
    level.player.invulnerability = 0;
    level.player.hitbox = (Rectangle){0, 0, 0.032, 0.048f};
    level.player.currentFrame = 0;
    level.player.timeSinceLastUpdate = 0;
    level.player.animationSpeed = 0.07f;
    level.player.textureOffset = (Vector2){-0.009f, -0.012f};
    level.player.textureRec = (Rectangle){0, 0, 0.048f, 0.072f};
    level.player.speed = 0.3f;
    level.player.timeSinceDeath = 0;
    level.player.color = WHITE;
    strcpy(level.assets.playerTexturePath, "assets/textures/player/blue.png");

    // Save struct to file
    SaveLevel(levelNumber, &level);
}

void UpdateLevel(Level *level)
{
    // Restart level
    if (IsKeyPressed(KEY_R))
        *level = LoadLevel(level->number);

    // Update player
    if (level->player.lives > 0)
    {
        UpdateGuns(&level->arena.gunArray);

        UpdatePlayer(&level->player, &level->arena);

        ShootGuns(&level->arena.gunArray, &level->arena.bulletArray);

        UpdateBullets(&level->arena.bulletArray, level->arena.center);
    }
    else
    {
        level->player.timeSinceDeath += deltaTime;
    }

    UpdateExplosions(&level->arena.explosionArray);

    if (!level->player.timeSinceDeath)
    {
        level->timer += deltaTime;
    }
    else
    {
        if (!level->player.isDead)
        {
            InitializeDeathScreen(level);
            level->player.isDead = true;
        }
        UpdateDeathScreen(level);
    }
}

void DrawLevel(Level *level)
{
    DrawArena(&level->arena);

    DrawPlayer(&level->player);

    DrawBullets(&level->arena.bulletArray);

    DrawGuns(&level->arena.gunArray);

    DrawExplosions(&level->arena.explosionArray);

    DrawText(TextFormat("Lives: %d", level->player.lives), 0.06f*(float)gameSize, 0.07f*(float)gameSize, 0.03f*(float)gameSize, RAYWHITE);
    DrawText(TextFormat("%.2f", level->timer), gameSize - (0.15f*(float)gameSize), 0.05f*(float)gameSize, 0.03f*(float)gameSize, RAYWHITE);

    if (level->player.timeSinceDeath)
    {
        DrawDeathScreen(&level->deathScreen);
    }

    // DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), 0, 0, 40, RED);
}