#ifndef GAME_H
#define GAME_H
#include "raylib.h"

enum Direction {
    NORTH = 0,
    NORTH_EAST = 16,
    EAST = 32,
    SOUTH_EAST = 48,
    SOUTH = 64,
    SOUTH_WEST = 80,
    WEST = 96,
    NORTH_WEST = 112
};

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
    int direction; 
    Rectangle hitbox;
    Texture2D playerTexture;
    float timeSinceDeath;
    float animationSpeed;
    float timeSinceLastUpdate;
    int currentFrame;
    Color color;
    Rectangle textureRec;
    Vector2 textureOffset;
} Player;

typedef struct Explosion {
    Rectangle hitbox;
    float timeSinceLastUpdate;
    int currentFrame;

} Explosion;

typedef struct ExplosionArray {
    Texture2D explosionTexture;
    Vector2 explosionSize;
    float animationSpeed;
    Explosion *explosions;
    int size;
    int logicalSize;
} ExplosionArray;

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
    ExplosionArray explosionArray;
} Arena;

typedef struct Textures {
    char gunTexturePath[64];
    char backgroundTexturePath[64];
    char playerTexturePath[64];
    char bulletTexturePath[64];
    char explosionTexturePath[64];
} Textures;

typedef struct Level {
    int number;
    Arena arena;
    Player player;
    Textures textures;
    Font font;
    float timer;
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
Vector2 CheckCollisionRotatedRecs(Rectangle rectangle1, float angle1, Rectangle rectangle2, float angle2);
void DrawTitleScreen();
void DrawExplosions(ExplosionArray *explosionArray);
void UpdateExplosions(ExplosionArray *explosionArray, float deltaTime);

#endif