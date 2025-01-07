#include "level.h"
#include "stdio.h"
#include "game.h"
#include "death_screen.h"
#include "string.h"

Color deathRed = (Color){126, 0, 7, 255};

void InitializeDeathScreen(Level *level)
{
    DeathScreen *deathScreen = &level->deathScreen;
    strcpy(deathScreen->message, "YOU DIED");

    sprintf(deathScreen->timer, "TIME: %.2fs", level->timer);

    deathScreen->animationDelay = 0.5f;
    deathScreen->animationDuration = 1.0f;
    deathScreen->messageFontSize = 0.15f * (float)gameSize;
    deathScreen->messageSpacing = 0.06f * deathScreen->messageFontSize;

    deathScreen->timerFontSize = 0.06f * (float)gameSize;
    deathScreen->timerSpacing = 0.06f * deathScreen->timerFontSize;

    deathScreen->messageSize = MeasureTextEx(gameFont, deathScreen->message, deathScreen->messageFontSize, deathScreen->messageSpacing);
    deathScreen->messagePosition = (Vector2){gameSize / 2 - deathScreen->messageSize.x / 2, gameSize / 4 - deathScreen->messageSize.y / 2};

    deathScreen->timerSize = MeasureTextEx(gameFont, deathScreen->timer, deathScreen->timerFontSize, deathScreen->timerSpacing);
    deathScreen->timerPosition = (Vector2){gameSize / 2 - deathScreen->timerSize.x / 2, gameSize / 4 + 1.2f * deathScreen->messageSize.y - deathScreen->timerSize.y / 2};

    deathScreen->buttons.count = 2;
    deathScreen->buttons.margin = 0.02f * gameSize;
    deathScreen->buttons.fontSize = 0.05f * gameSize;
    strcpy(deathScreen->buttons.names[0], "Restart");
    strcpy(deathScreen->buttons.names[1], "Main menu");
    deathScreen->buttons.selected = 0;
}

void UpdateDeathScreen(Level *level)
{
    DeathScreen *deathScreen = &level->deathScreen;

    if (level->player.timeSinceDeath < deathScreen->animationDelay + deathScreen->animationDuration && level->player.timeSinceDeath > deathScreen->animationDelay)
    {
        deathScreen->opacity = (level->player.timeSinceDeath - deathScreen->animationDelay) / deathScreen->animationDuration * 255.0f;
    }
    else if (level->player.timeSinceDeath <= deathScreen->animationDelay)
    {
        deathScreen->opacity = 0;
    }
    else
    {
        deathScreen->opacity = 255;
    }

    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && deathScreen->buttons.selected < deathScreen->buttons.count - 1 && level->player.timeSinceDeath > 1.5f)
        deathScreen->buttons.selected += 1;
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && deathScreen->buttons.selected > 0 && level->player.timeSinceDeath > 1.5f)
        deathScreen->buttons.selected -= 1;

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        if (deathScreen->buttons.selected == 0)
        {
            *level = LoadLevel(level->number);
        }
        else if (deathScreen->buttons.selected == 1)
        {
            gameState = MAIN_MENU;
        }
    }
}

void DrawDeathScreen(DeathScreen *deathScreen)
{
    Color color = deathRed;
    color.a = deathScreen->opacity;

    DrawRectangle(0, 0, gameSize, gameSize, (Color){0, 0, 0, color.a});
    DrawTextEx(gameFont, deathScreen->message, deathScreen->messagePosition, deathScreen->messageFontSize, deathScreen->messageSpacing, color);
    DrawTextEx(gameFont, deathScreen->timer, deathScreen->timerPosition, deathScreen->timerFontSize, deathScreen->timerSpacing, (Color){255, 255, 255, color.a});

    for (int i = 0; i < deathScreen->buttons.count; i++)
    {
        color = (deathScreen->buttons.selected == i) ? deathRed : WHITE;
        color.a = deathScreen->opacity;

        Vector2 textSize = MeasureTextEx(gameFont, deathScreen->buttons.names[i], deathScreen->buttons.fontSize, 0.06f * deathScreen->buttons.fontSize);
        Vector2 textPosition = {gameSize / 2 - textSize.x / 2, (float)gameSize / 1.7f + textSize.y * i + deathScreen->buttons.margin * i};
        DrawTextEx(gameFont, deathScreen->buttons.names[i], textPosition, deathScreen->buttons.fontSize, 0.06f * deathScreen->buttons.fontSize, color);
    }
}