#ifndef COLLISON_H
#define COLLISON_H

#include "raylib.h"

void GetRotatedRecCorners(Vector2 *corners, Rectangle rec, float angle);
Vector2 CheckCollisionRotatedRecs(Rectangle rectangle1, float angle1, Rectangle rectangle2, float angle2);

#endif