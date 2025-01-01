#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "arena.h"

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

void DrawPlayer(Player *player);
void UpdatePlayer(Player *player, Arena *arena, float deltaTime);


#endif