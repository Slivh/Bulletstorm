#ifndef GUN_H
#define GUN_H

#include "raylib.h"
#include "bullets.h"

typedef struct Gun
{
    int x, y;
    int side;
    float timeSinceLastShot;
    float timeBetweenShot;
    float timeSinceLastUpdate;
    int currentFrame;
} Gun;

typedef struct GunArray
{
    Texture2D gunTexture;
    float animationSpeed;
    float gunOffset;
    float gunScaling;
    float gunTextureOffset;
    bool isGunRotated;
    int numberOfGunsPerSide;
    float gunAreaSize;
    float gunFireDelay;
    float gunFireDelayDeviation;
    int gunFireAngleDeviation;
    Sound firingSound;
    Gun *guns;
} GunArray;

enum Side
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

void CreateGuns(GunArray *gunArray, int arenaCenterSize);
void DrawGuns(GunArray *gunArray);
void ShootGuns(GunArray *gunArray, BulletArray *bulletArray);
void UpdateGuns(GunArray *gunArray);

#endif