#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include <stdlib.h>
#include "collision.h"
#include "stdio.h"
#include "game.h"

void DrawPlayer(Player *player) {

    player->color = WHITE;

    // Make player if has 1 life
    if (player->lives == 1) {
        player->color = RED;
    }

    // Make player green if invulnerable
    if (player->invulnerability > 0) {
        player->color = GREEN;
    }

    // Make player black if dead
    if (player->lives == 0) {
        player->color = BLACK;
    }

    // Draw player
    DrawTexturePro(player->playerTexture, (Rectangle){player->direction, player->currentFrame*24, 16, 24}, player->textureRec, Vector2Zero(), 0, player->color);
    
    // Draw player hitbox
    // DrawRectangleLines(player->hitbox.x, player->hitbox.y, player->hitbox.width, player->hitbox.height, player->color);

}

void UpdatePlayer(Player *player, Arena *arena) {
    
    Vector2 direction = {0};

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction.y += 1;
    
    // Update player direction
    switch ((int)(Vector2Angle((Vector2){1, 0}, direction) * (180.0f / PI))) {
        case 0:
            if (!direction.x) {
                player->direction = SOUTH;
                break;
            }
            player->direction = EAST;
            break;
        case 1 ... 22:
            player->direction = EAST;
            break;
        case 23 ... 67:
            player->direction = SOUTH_EAST;
            break;
        case 68 ... 112:
            player->direction = SOUTH;
            break;
        case 113 ... 157:
            player->direction = SOUTH_WEST;
            break;
        case 158 ... 180:
            player->direction = WEST;
            break;
        case -180 ... -158:
            player->direction = WEST;
            break;
        case -157 ... -113:
            player->direction = NORTH_WEST;
            break;
        case -112 ... -68:
            player->direction = NORTH;
            break;
        case -67 ... -23:
            player->direction = NORTH_EAST;
            break;
        case -22 ... -1:
            player->direction = EAST;
            break;
    }

    // slows down when diagonal on walls
    direction = Vector2Scale(Vector2Normalize(direction), deltaTime*player->speed);

    // Add direction to exisiting position
    Vector2 newPlayerPosition = Vector2Add((Vector2){player->hitbox.x, player->hitbox.y}, direction);

    // Clamp player inside arena boundaries
    newPlayerPosition.x = Clamp(newPlayerPosition.x, arena->center.x, arena->center.x + arena->center.width - player->hitbox.width);
    newPlayerPosition.y = Clamp(newPlayerPosition.y, arena->center.y, arena->center.y + arena->center.height - player->hitbox.height);
    
    // Update player hitbox
    player->hitbox = (Rectangle){newPlayerPosition.x, newPlayerPosition.y, player->hitbox.width, player->hitbox.height};

    // Update invulnerability
    if (player->invulnerability > 0) {
        player->invulnerability -= deltaTime;
        if (player->invulnerability < 0) {
            player->invulnerability = 0;
        }
    }
    
    // Check if player is hit
    for (int i=0; i<arena->bulletArray.logicalSize; i++) {

        Vector2 collisionPt = CheckCollisionRotatedRecs(player->hitbox, 0, arena->bulletArray.bullets[i].hitbox, arena->bulletArray.bullets[i].angle);
        
        if (Vector2Length(collisionPt) && player->invulnerability == 0) {
            
            // Remove 1 life and apply invulnerability
            player->lives -= 1;
            player->invulnerability = 2;

            // Create explosion
            if (arena->explosionArray.size == arena->explosionArray.logicalSize) {
                arena->explosionArray.explosions = realloc(arena->explosionArray.explosions, sizeof(Explosion)*(arena->explosionArray.size+1));
                arena->explosionArray.size++;
            }

            int x = collisionPt.x;            
            int y = collisionPt.y;
            int width = arena->explosionArray.explosionSize.x;
            int height = arena->explosionArray.explosionSize.y;

            // Create explosion
            arena->explosionArray.explosions[arena->explosionArray.logicalSize] = (Explosion){(Rectangle){x, y, width, height}, 0, 0};
            arena->explosionArray.logicalSize++;

            // Delete bullet
            arena->bulletArray.bullets[i] = arena->bulletArray.bullets[arena->bulletArray.logicalSize - 1];
            arena->bulletArray.logicalSize--;
            i--;
        }
    }

    // Update texture rectangle coords to match hitbox
    player->textureRec.x = player->hitbox.x + player->textureOffset.x;
    player->textureRec.y = player->hitbox.y + player->textureOffset.y;

    // Update player animation frame
    if (player->timeSinceLastUpdate < player->animationSpeed) {
        player->timeSinceLastUpdate += deltaTime;
    } else {
        if (Vector2Length(direction)) {
            if (player->currentFrame == 2) {
                player->currentFrame = 0;
            } else {
                player->currentFrame++;
            }
            player->timeSinceLastUpdate = 0;
        } else {
            player->currentFrame = 1;
        }
        
    }

    if (player->lives == 0) {
        player->timeSinceDeath =+ deltaTime;
    }
}