#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

#include "buttons.h"

extern Color deathRed;

typedef struct Level Level;

typedef struct DeathScreen
{
    char message[16];
    char timer[16];
    float animationDelay;
    float animationDuration;
    int opacity;
    float messageFontSize;
    float messageSpacing;
    float timerFontSize;
    float timerSpacing;
    Vector2 messageSize;
    Vector2 messagePosition;
    Vector2 timerSize;
    Vector2 timerPosition;
    Buttons buttons;
    // KEEP MUSIC LAST ELEMENT
    Music music;
} DeathScreen;

void InitializeDeathScreen(Level *level);
void UpdateDeathScreen(Level *level);
void DrawDeathScreen(DeathScreen *deathScreen);

#endif