#include "explosions.h"
#include "raylib.h"
#include "game.h"

void UpdateExplosions(ExplosionArray *explosionArray)
{
    for (int i = 0; i < explosionArray->logicalSize; i++)
    {

        if (explosionArray->explosions[i].timeSinceLastUpdate < explosionArray->animationSpeed)
        {
            explosionArray->explosions[i].timeSinceLastUpdate += deltaTime;
        }
        else
        {
            if (explosionArray->explosions[i].currentFrame == 8)
            {
                explosionArray->explosions[i] = explosionArray->explosions[explosionArray->logicalSize - 1];
                explosionArray->logicalSize--;
                i--;
            }
            else
            {
                explosionArray->explosions[i].currentFrame++;
                explosionArray->explosions[i].timeSinceLastUpdate = 0;
            }
        }
    }
}

void DrawExplosions(ExplosionArray *explosionArray)
{
    for (int i = 0; i < explosionArray->logicalSize; i++)
    {
        DrawTexturePro(explosionArray->explosionTexture, (Rectangle){explosionArray->explosions[i].currentFrame * 32, 0, 32, 32}, explosionArray->explosions[i].hitbox, (Vector2){0, 0}, 0, WHITE);
    }
}