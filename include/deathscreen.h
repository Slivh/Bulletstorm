#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

typedef struct Level Level;

void UpdateDeathScreen(Level *level, int gameSize);
void DrawDeathScreen(Level *level, int gameSize);

#endif