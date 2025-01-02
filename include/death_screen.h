#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

extern Color deathRed;

typedef struct Level Level;

void UpdateDeathScreen(Level *level);
void DrawDeathScreen(Level *level);

#endif