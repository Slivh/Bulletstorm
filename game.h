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
    float invulnerability;
    Rectangle hitbox;
    Texture2D playerTexture;
    float timeSinceDeath;
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
    float gunFireDelay;
    float gunFireDelayDeviation;
    int gunFireAngleDeviation;
    Gun *guns;
} GunArray;

typedef struct Bullet {
    Rectangle hitbox;
    Vector2 direction;
    float angle;
    bool reachedCenter;
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
    Font alagard;
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

typedef struct Polygon {
    Vector2 *vertices;
    int vertexCount;
} Polygon;

void CreateGuns(GunArray *gunArray, int arenaCenterSize);
void DrawArena(Arena *arena, int gameSize);
void DrawGuns(GunArray *gunArray);
void DrawPlayer(Player *player);
void UpdatePlayer(Player *player, Arena *arena, float deltaTime);
void SaveLevel(int levelNumber, Level *level);
Level LoadLevel(int levelNumber, Game *game);
void CreateLevel(int levelNumber);
void LoadTextures(Level *level);
void ShootGuns(GunArray *gunArray, BulletArray *bulletArray, float deltaTime);
void UpdateBullets(BulletArray *bulletArray, Rectangle arenaCenter, float deltaTime);
void DrawBullets(BulletArray *bulletArray);
void GetRotatedRecCorners(Vector2 *corners, Rectangle rec, float angle);
bool CheckCollisionRotatedRecs(Rectangle rectangle1, float angle1, Rectangle rectangle2, float angle2);
void DrawTitleScreen();
#endif