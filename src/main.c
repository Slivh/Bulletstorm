#include "raylib.h"
#include <stdio.h>
#include "level.h"
#include "game.h"

int main() {
    Game game;

    game.windowWidth = 1400;
    game.windowHeight = 1400;
    
    InitializeGame(&game);

    CreateLevel(1);

    while (!WindowShouldClose()) {
        
        UpdateGame(&game);

        DrawGame(&game);
        
    }
    CloseWindow();

    return 0;
}