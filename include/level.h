#ifndef LEVEL_H
#define LEVEL_H

typedef struct Game Game;

#include "raylib.h"
#include "arena.h"
#include "player.h"
#include "assets.h"
#include "death_screen.h"

typedef struct Level {
    int number;
    Arena arena;
    Player player;
    Assets assets;
    float timer;
    DeathScreen deathScreen;
} Level;

void SaveLevel(int levelNumber, Level *level);
Level LoadLevel(int levelNumber);
void CreateLevel(int levelNumber);
void UpdateLevel(Level *level);
void DrawLevel(Level *level);

#endif