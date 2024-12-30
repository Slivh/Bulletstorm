#include "raylib.h"
#include "raymath.h"
#include "game.h"

void DrawPlayer(Player *player) {

    Color playerColor;

    switch (player->lives) {
    case 3:
        playerColor = GREEN;
        break;
    
    case 2:
        playerColor = YELLOW;
        break;

    case 1:
        playerColor = RED;
        break;

    case 0:
        playerColor = BLACK;
        break;

    default:
        playerColor = WHITE;
    }

    DrawRectangle(player->hitbox.x, player->hitbox.y, player->hitbox.width, player->hitbox.height, playerColor);
}

void UpdatePlayer(Player *player, Arena *arena, float deltaTime) {
    Vector2 direction = {0};

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction.y += 1;

    // slows down when on walls
    Vector2 newPlayerPosition = Vector2Add((Vector2){player->hitbox.x, player->hitbox.y}, Vector2Scale(Vector2Normalize(direction), deltaTime*player->speed));

    newPlayerPosition.x = Clamp(newPlayerPosition.x, arena->center.x + player->hitbox.width/2, arena->center.x + arena->center.width - player->hitbox.width/2);
    newPlayerPosition.y = Clamp(newPlayerPosition.y, arena->center.y + player->hitbox.height/2, arena->center.y + arena->center.height - player->hitbox.height/2);

    player->hitbox = (Rectangle){newPlayerPosition.x, newPlayerPosition.y, player->hitbox.width, player->hitbox.height};

    if (player->invulnerability > 0) {
        player->invulnerability -= deltaTime;
        if (player->invulnerability < 0) {
            player->invulnerability = 0;
        }
    }
    
    for (int i=0; i<arena->bulletArray.logicalSize; i++) {
        if (CheckCollisionRotatedRecs(player->hitbox, 0, arena->bulletArray.bullets[i].hitbox, arena->bulletArray.bullets[i].angle) && player->invulnerability == 0) {
            player->lives -= 1;
            player->invulnerability = 2;
        }
    }
    
}