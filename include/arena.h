#ifndef ARENA_H
#define ARENA_H

#include "raylib.h"
#include "gun.h"
#include "bullets.h"
#include "explosions.h"

typedef struct Arena
{
    Texture2D backgroundTexture;
    Rectangle center;
    GunArray gunArray;
    BulletArray bulletArray;
    ExplosionArray explosionArray;
} Arena;

void DrawArena(Arena *arena);

#endif