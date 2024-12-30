#include "raylib.h"
#include "game.h"
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
#include "raymath.h"

void CreateGuns(GunArray *gunArray, int arenaCenterSize) {
    gunArray->guns = (Gun*)malloc(gunArray->numberOfGunsPerSide*4 * sizeof(Gun));

    int x, y, gunSide;
    
    for (int side=0; side<4; side++) {
        for (int i=0; i<gunArray->numberOfGunsPerSide; i++) {
            if (side == 0) {
                gunSide = LEFT;
                x = gunArray->gunAreaSize/2 + gunArray->gunOffset*gunArray->gunAreaSize;
                y = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
            } else if (side == 1) {
                gunSide = RIGHT;
                x = gunArray->gunAreaSize*1.5f + arenaCenterSize - gunArray->gunOffset*gunArray->gunAreaSize;
                y = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
            } else if (side == 2) {
                gunSide = TOP;
                x = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
                y = gunArray->gunAreaSize/2 + gunArray->gunOffset*gunArray->gunAreaSize;
            } else {
                gunSide = BOTTOM;
                x = gunArray->gunAreaSize + (i+1)*(arenaCenterSize/(gunArray->numberOfGunsPerSide+1));
                y = gunArray->gunAreaSize*1.5f + arenaCenterSize - gunArray->gunOffset*gunArray->gunAreaSize;
            }
            
            int timeBetweenShot = GetRandomValue(gunArray->gunFireDelay - gunArray->gunFireDelayDeviation, gunArray->gunFireDelay + gunArray->gunFireDelayDeviation);

            // add random delay before 1st shot
            float delay = (float)GetRandomValue(100, 1000) / 1000;

            gunArray->guns[side*gunArray->numberOfGunsPerSide + i] = (Gun){x, y, gunSide, delay, timeBetweenShot};
        }
    }
}

void DrawGuns(GunArray *gunArray) { 
    int gunSize = gunArray->gunScaling*gunArray->gunAreaSize;
    int gunSizeX, gunSizeY;

    float gunRatio = (float) gunArray->gunTexture.width/gunArray->gunTexture.height;

    if (gunRatio < 1) {
        gunSizeX = gunSize*gunRatio;
        gunSizeY = gunSize;
    } else {
        gunSizeX = gunSize;
        gunSizeY = gunSize/gunRatio;
    }

    for (int i=0; i<gunArray->numberOfGunsPerSide*4; i++) {
        int flipY = 1;
        float rotation = 0.0f;

        switch (gunArray->guns[i].side) {
            case RIGHT: 
                flipY = -1;
                break;
            case TOP: 
                rotation = 90.0f;
                break;
            case BOTTOM: 
                rotation = 270.0f;
                break;
        }

        if (!gunArray->isGunRotated) {
            flipY = 1;
            rotation = 0.0f;
        }
        DrawTexturePro(
            gunArray->gunTexture,
            (Rectangle) {0, 0, flipY*gunArray->gunTexture.width, gunArray->gunTexture.height}, 
            (Rectangle) {gunArray->guns[i].x, gunArray->guns[i].y + gunArray->gunTextureOffset*gunArray->gunAreaSize, gunSizeX, gunSizeY},
            (Vector2) { gunSizeX/2, gunSizeY/2}, 
            rotation, 
            WHITE
        );
        DrawRectangle(gunArray->guns[i].x, gunArray->guns[i].y, 5, 5, PURPLE);
    }
}

void ShootGuns(GunArray *gunArray, BulletArray *bulletArray, float deltaTime) {
    for (int i=0; i<gunArray->numberOfGunsPerSide*4; i++) {
        if (gunArray->guns[i].timeSinceLastShot >= gunArray->guns[i].timeBetweenShot) {

            // realloc array if needed
            if (bulletArray->size == bulletArray->logicalSize) {
                bulletArray->bullets = realloc(bulletArray->bullets, sizeof(Bullet)*(bulletArray->size+1));
                bulletArray->size++;
            }

            int bulletX = gunArray->guns[i].x;
            int bulletY = gunArray->guns[i].y;
            Rectangle bulletHitbox = {bulletX, bulletY, bulletArray->bulletSize.x, bulletArray->bulletSize.y};

            int bulletAngle = 0;

            switch (gunArray->guns[i].side) {                    
                case RIGHT: 
                    bulletAngle = 180;
                    break;
                case TOP: 
                    bulletAngle = 90;
                    break;
                case BOTTOM: 
                    bulletAngle = 270;
                    break;
            }

            bulletAngle += GetRandomValue(-gunArray->gunFireAngleDeviation, gunArray->gunFireAngleDeviation);

            Vector2 bulletDirection = {1, 0};

            float bulletAngleRadians = bulletAngle * (PI / 180.0);

            bulletDirection = Vector2Rotate(bulletDirection, bulletAngleRadians);

            bulletDirection = Vector2Scale(bulletDirection, deltaTime*bulletArray->bulletSpeed);


            bulletArray->bullets[bulletArray->logicalSize] = (Bullet){bulletHitbox, bulletDirection, bulletAngleRadians};


            bulletArray->logicalSize++;

            gunArray->guns[i].timeSinceLastShot = 0.0f;

            float minRate = (gunArray->gunFireDelay - gunArray->gunFireDelayDeviation) * 1000;
            float maxRate = (gunArray->gunFireDelay + gunArray->gunFireDelayDeviation) * 1000;
            float randomFireRate = (float)GetRandomValue(minRate, maxRate) / 1000.0f;

            gunArray->guns[i].timeBetweenShot = randomFireRate;
        } else {
            gunArray->guns[i].timeSinceLastShot += deltaTime;
        }
    }
}

void UpdateBullets(BulletArray *bulletArray) {
    for (int i=0; i<bulletArray->logicalSize; i++) {
        bulletArray->bullets[i].hitbox.x += bulletArray->bullets[i].direction.x;
        bulletArray->bullets[i].hitbox.y += bulletArray->bullets[i].direction.y;
    }
}

void DrawBullets(BulletArray *bulletArray) {
    for (int i=0; i<bulletArray->logicalSize; i++) {
        
        // DrawRectangleRec(bulletArray->bullets[i].hitbox, RED);
        DrawTexturePro(
            bulletArray->bulletTexture,
            (Rectangle){0, 0, bulletArray->bulletTexture.width, bulletArray->bulletTexture.height},
            bulletArray->bullets[i].hitbox,
            (Vector2){bulletArray->bullets[i].hitbox.width/2, bulletArray->bullets[i].hitbox.height/2},
            bulletArray->bullets[i].angle * (180.0f / PI),
            WHITE
        );
    }
}
