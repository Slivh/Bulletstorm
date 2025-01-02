#include "level.h"
#include "stdio.h"
#include "game.h"
#include "death_screen.h"

Color deathRed = (Color){126, 0, 7, 255};

void DrawDeathScreen(Level *level) {
    float messageDelay = 0.5f;
    float messageAnimationDuration = 1.0f;
    Color deathRed = (Color){126, 0, 7, 255};

    float messageFontSize = 0.15f*(float)gameSize;
    float messageSpacing = 0.06f*messageFontSize;

    float timerFontSize = 0.05f*(float)gameSize;
    float timerSpacing = 0.06f*timerFontSize;  
    
    char message[] = "YOU DIED";
    char timer[16];
    sprintf(timer, "TIME: %.2fs", level->timer);

    Vector2 messageSize = MeasureTextEx(level->font, message, messageFontSize, messageSpacing);
    Vector2 messagePosition = {gameSize/2 - messageSize.x/2, gameSize/4 - messageSize.y/2};

    Vector2 timerSize = MeasureTextEx(level->font, timer, timerFontSize, timerSpacing);
    Vector2 timerPosition = {gameSize/2 - timerSize.x/2, gameSize/4 + 1.2f*messageSize.y - timerSize.y/2};


    if (level->player.timeSinceDeath < messageDelay + messageAnimationDuration && level->player.timeSinceDeath > messageDelay) {
        deathRed.a = (level->player.timeSinceDeath - messageDelay) / messageAnimationDuration * 255.0f;
    } else if (level->player.timeSinceDeath <= messageDelay){
        deathRed.a = 0;
    } else {
        deathRed.a = 255;
    }

    DrawRectangle(0, 0, gameSize, gameSize, (Color){0, 0, 0, deathRed.a});
    DrawTextEx(level->font, message, messagePosition, messageFontSize, messageSpacing, deathRed);
    DrawTextEx(level->font, timer, timerPosition, timerFontSize, timerSpacing, deathRed);
}

void UpdateDeathScreen(Level *level) {

}