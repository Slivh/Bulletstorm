#include "raylib.h"
#include "game.h"
#include "time.h"

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
    
}

void UpdateBullets(Arena *arena) {
}

void DrawBullets(Arena *arena) {
}
