#include "bullets.h"
#include "game.h"

void UpdateBullets(BulletArray *bulletArray, Rectangle arenaCenter)
{
    for (int i = 0; i < bulletArray->logicalSize; i++)
    {
        bulletArray->bullets[i].hitbox.x += bulletArray->bullets[i].direction.x * deltaTime;
        bulletArray->bullets[i].hitbox.y += bulletArray->bullets[i].direction.y * deltaTime;
        if (!CheckCollisionRecs(bulletArray->bullets[i].hitbox, arenaCenter))
        {
            if (bulletArray->bullets[i].reachedCenter)
            {
                bulletArray->bullets[i] = bulletArray->bullets[bulletArray->logicalSize - 1];
                bulletArray->logicalSize--;
                i--;
            }
        }
        else
        {
            bulletArray->bullets[i].reachedCenter = true;
        }
    }
}

void DrawBullets(BulletArray *bulletArray)
{
    for (int i = 0; i < bulletArray->logicalSize; i++)
    {
        DrawTexturePro(
            bulletArray->bulletTexture,
            (Rectangle){0, 0, bulletArray->bulletTexture.width, bulletArray->bulletTexture.height},
            (Rectangle){
                bulletArray->bullets[i].hitbox.x + bulletArray->bullets[i].hitbox.width / 2,
                bulletArray->bullets[i].hitbox.y + bulletArray->bullets[i].hitbox.height / 2,
                bulletArray->bullets[i].hitbox.width,
                bulletArray->bullets[i].hitbox.height},
            (Vector2){bulletArray->bullets[i].hitbox.width / 2, bulletArray->bullets[i].hitbox.height / 2},
            bulletArray->bullets[i].angle * (180.0f / PI),
            WHITE
        );
    }
}         