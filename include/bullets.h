#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"

typedef struct Bullet
{
    Rectangle hitbox;
    Vector2 direction;
    float angle;
    bool reachedCenter;
} Bullet;

typedef struct BulletArray
{
    Texture2D bulletTexture;
    Vector2 bulletSize;
    float bulletSpeed;
    Bullet *bullets;
    int size;
    int logicalSize;
} BulletArray;

void UpdateBullets(BulletArray *bulletArray, Rectangle arenaCenter);
void DrawBullets(BulletArray *bulletArray);

#endif