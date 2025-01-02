#ifndef EXPLOSIONS_H
#define EXPLOSIONS_H

#include "raylib.h"


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

void UpdateExplosions(ExplosionArray *explosionArray);
void DrawExplosions(ExplosionArray *explosionArray);

#endif