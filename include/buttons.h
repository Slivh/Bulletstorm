#ifndef BUTTONS_H
#define BUTTONS_H

#include "raylib.h"

typedef struct Buttons {
    int count;
    char names[8][16];
    float fontSize;
    float margin;
    int selected;
} Buttons;

#endif