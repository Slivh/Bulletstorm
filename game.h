#ifndef GAME_H
#define GAME_H
#include "raylib.h"

enum Side {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

typedef struct Player {
    int lives;
    float speed;
    Rectangle hitbox;
    Texture2D playerTexture;
} Player;

typedef struct Gun {
    int x, y;
    int side;
    float timeSinceLastShot;
    float timeBetweenShot;
} Gun;

typedef struct GunArray {    
    Texture2D gunTexture;
    float gunOffset;
    float gunScaling;
    float gunTextureOffset;
    bool isGunRotated;
    int numberOfGunsPerSide;
    float gunAreaSize;
    float gunFireRate;
    float gunFireRateDeviation;
    int gunFireAngleDeviation;
    Gun *guns;
} GunArray;

typedef struct Bullet {
    Rectangle hitbox;
    Vector2 direction;
} Bullet;

typedef struct BulletArray {
    Texture2D bulletTexture;
    Vector2 bulletSize;
    float bulletSpeed;
    Bullet *bullets;
    int size;
    int logicalSize;
} BulletArray;

typedef struct Arena {
    Texture2D backgroundTexture;
    Rectangle center;
    GunArray gunArray;
    BulletArray bulletArray;
} Arena;

typedef struct Textures {
    char gunTexturePath[32];
    char backgroundTexturePath[32];
    char playerTexturePath[32];
    char bulletTexturePath[32];
} Textures;

typedef struct Level {
    int number;
    Arena arena;
    Player player;
    Textures textures;
} Level;

typedef struct Game {
    bool fullscreen;
    int size;
    int offsetX;
    int offsetY;
    int windowWidth;
    int windowHeight;
    Camera2D camera;
    Level level;
} Game;





void CreateGuns(GunArray *gunArray, int arenaCenterSize);
void DrawArena(Arena *arena, int gameSize);
void DrawGuns(GunArray *gunArray);
void DrawPlayer(Player *player);
void UpdatePlayer(Player *player, Arena *arena, float deltaTime);
void SaveLevel(int levelNumber, Level *level);
Level LoadLevel(int levelNumber, Game *game);
void CreateLevel();
void LoadTextures(Level *level);
void ShootGuns(GunArray *gunArray, BulletArray *bulletArray, float deltaTime);
void UpdateBullets(BulletArray *bulletArray);
void DrawBullets(BulletArray *bulletArray);
#endif