#ifndef GUN_H
#define GUN_H

#include "raylib.h"
#include "bullets.h"

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

enum Side {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

void CreateGuns(GunArray *gunArray, int arenaCenterSize);
void DrawGuns(GunArray *gunArray);
void ShootGuns(GunArray *gunArray, BulletArray *bulletArray, float deltaTime);


#endif