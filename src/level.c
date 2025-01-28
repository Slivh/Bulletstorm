#include "raylib.h"
#include <stdio.h>
#include "level.h"
#include "raymath.h"
#include <stdlib.h>
#include <string.h>
#include "death_screen.h"
#include "game.h"
#include "assets.h"

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

    level.arena.bulletArray.bullets = (Bullet*)malloc(1);
    level.arena.bulletArray.bulletSpeed *= gameSize;

    level.arena.explosionArray.explosionSize = Vector2Scale(level.arena.explosionArray.explosionSize, gameSize);
    level.arena.explosionArray.explosions = (Explosion*)malloc(1);

    LoadLevelAssets(&level);

    return level;
}

void CreateLevel(int levelNumber)
{
    Level level;
    char season[16];
    switch (levelNumber)
    {
        case 0:
            strcpy(season, "spring");
            break;
        case 1:
            strcpy(season, "summer");
            break;
        case 2:
            strcpy(season, "autumn");
            break;
        case 3:
            strcpy(season, "winter");
            break;
    }
    strcpy(level.assets.backgroundTexturePath, TextFormat("assets/textures/arena/maps/%s.png", season));

    level.timer = 0;

    // Gun properties
    level.arena.gunArray.isGunRotated = true;
    level.arena.gunArray.numberOfGunsPerSide = 7 + levelNumber;
    level.arena.gunArray.gunAreaSize = 0.15f;
    level.arena.gunArray.gunTextureOffset = 0;
    level.arena.gunArray.gunOffset = 0.0f;
    level.arena.gunArray.gunScaling = 0.3f;
    level.arena.gunArray.gunFireDelay = 10 - levelNumber;
    level.arena.gunArray.gunFireDelayDeviation = 9 - levelNumber;
    level.arena.gunArray.gunFireAngleDeviation = 40;
    level.arena.gunArray.animationSpeed = 0.05f;
    strcpy(level.assets.gunTexturePath, "assets/textures/arena/guns/drone.png");
    strcpy(level.assets.firingSoundPath, "assets/audio/sound/pew.wav");

    // Bullet properties
    level.arena.bulletArray.bulletSize = (Vector2){0.025f, 0.01};
    level.arena.bulletArray.bulletSpeed = 0.25f + (float)levelNumber/10.0f;
    level.arena.bulletArray.size = 0;
    strcpy(level.assets.bulletTexturePath, "assets/textures/arena/guns/laser.png");

    // Explosions properties
    level.arena.explosionArray.animationSpeed = 0.05f;
    level.arena.explosionArray.explosionSize = (Vector2){0.025f, 0.025f};
    level.arena.explosionArray.size = 0;
    strcpy(level.assets.explosionTexturePath, "assets/textures/arena/guns/explosion.png");
    strcpy(level.assets.explosionSoundPath, "assets/audio/sound/explosion.ogg");

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

    char color[16];
    switch (levelNumber)
    {
        case 0:
            strcpy(color, "blue");
            break;
        case 1:
            strcpy(color, "blue");
            break;
        case 2:
            strcpy(color, "orange");
            break;
        case 3:
            strcpy(color, "white");
            break;
    }
    strcpy(level.assets.playerTexturePath, TextFormat("assets/textures/player/%s.png", color));
    strcpy(level.assets.deathSoundPath, "assets/audio/sound/gameover.wav");

    strcpy(level.assets.heartFullTexturePath, "assets/textures/player/heart/heart_full.png");
    strcpy(level.assets.heartEmptyTexturePath, "assets/textures/player/heart/heart_empty.png");

    int music = levelNumber;
    if (music ==  0)
        music = 1;

    strcpy(level.assets.levelMusicPath, TextFormat("assets/audio/music/%d.mp3", music));
    strcpy(level.assets.deathScreenMusicPath, "assets/audio/music/ending.mp3");

    // Save struct to file
    SaveLevel(levelNumber, &level);
}

void UpdateLevel(Level *level)
{
    // Restart level
    if (IsKeyPressed(KEY_R))
        RestartLevel(level);

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

        // Update music
        if (!IsMusicStreamPlaying(level->music))
        {
            PlayMusicStream(level->music);
            SetMusicVolume(level->music, 0.2f);
        }
        UpdateMusicStream(level->music);
    }
    else
    {
        if (!level->player.isDead)
        {
            InitializeDeathScreen(level);
            level->player.isDead = true;
            PlaySound(level->player.deathSound);
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

    DrawPlayerHealth(level->player.lives, level->player.heartFullTexture, level->player.heartEmptyTexture);
    DrawText(TextFormat("%.2f", level->timer), gameSize - (0.15f*(float)gameSize), 0.07f*(float)gameSize, 0.04f*(float)gameSize, RAYWHITE);

    if (level->player.timeSinceDeath)
    {
        DrawDeathScreen(&level->deathScreen);
    }
    // DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), 0, 0, 40, RED);
}

void RestartLevel(Level *level)
{
    // Reset player
    level->player.hitbox.x = gameSize / 2 - level->player.hitbox.width / 2;
    level->player.hitbox.y = gameSize / 2 - level->player.hitbox.height / 2;
    level->player.timeSinceDeath = 0;
    level->player.color = WHITE;
    level->player.currentFrame = 0;
    level->player.timeSinceLastUpdate = 0;
    level->player.isDead = false;
    level->player.lives = 3;
    level->player.invulnerability = 0;

    // Reset bullets
    level->arena.bulletArray.size = 0;
    level->arena.bulletArray.bullets = (Bullet*)malloc(1);

    // Reset explosions
    level->arena.explosionArray.size = 0;
    level->arena.explosionArray.explosions = (Explosion*)malloc(1);

    // Restart music
    SeekMusicStream(level->music, 0.0f);
    ResumeMusicStream(level->music);

    // Reset death screen
    memset(&level->deathScreen, 0, sizeof(level->deathScreen) - sizeof(Music));

    // Reset timer
    level->timer = 0.0f;


}