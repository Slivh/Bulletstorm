#ifndef LEVEL_H
#define LEVEL_H

typedef struct Game Game;

#include "raylib.h"
#include "arena.h"
#include "player.h"
#include "assets.h"

typedef struct Level {
    int number;
    Arena arena;
    Player player;
    Assets assets;
    Font font;
    float timer;
} Level;

void SaveLevel(int levelNumber, Level *level);
Level LoadLevel(int levelNumber, Game *game);
void CreateLevel(int levelNumber);
void UpdateLevel(Level *level, float deltaTime);
void DrawLevel(Level *level, int gameSize);

#endif