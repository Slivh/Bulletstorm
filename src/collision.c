#include "raylib.h"
#include "raymath.h"
#include "collision.h"

void GetRotatedRecCorners(Vector2 *corners, Rectangle rec, float angle)
{
    // Calculate the center of the rectangle
    float cx = rec.x + rec.width / 2;
    float cy = rec.y + rec.height / 2;

    // Calculate the corners relative to the center
    float halfWidth = rec.width / 2;
    float halfHeight = rec.height / 2;

    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    // Top-right corner
    corners[0].x = cx + (halfWidth * cosTheta) - (halfHeight * sinTheta);
    corners[0].y = cy + (halfWidth * sinTheta) + (halfHeight * cosTheta);

    // Top-left corner
    corners[1].x = cx - (halfWidth * cosTheta) - (halfHeight * sinTheta);
    corners[1].y = cy - (halfWidth * sinTheta) + (halfHeight * cosTheta);

    // Bottom-left corner
    corners[2].x = cx - (halfWidth * cosTheta) + (halfHeight * sinTheta);
    corners[2].y = cy - (halfWidth * sinTheta) - (halfHeight * cosTheta);

    // Bottom-right corner
    corners[3].x = cx + (halfWidth * cosTheta) + (halfHeight * sinTheta);
    corners[3].y = cy + (halfWidth * sinTheta) - (halfHeight * cosTheta);
}

Vector2 CheckCollisionRotatedRecs(Rectangle rectangle1, float angle1, Rectangle rectangle2, float angle2)
{

    Vector2 polygon1Vertices[4];
    Vector2 polygon2Vertices[4];

    GetRotatedRecCorners(polygon1Vertices, rectangle1, angle1);
    GetRotatedRecCorners(polygon2Vertices, rectangle2, angle2);

    for (int i = 0; i < 4; i++)
    {
        bool collision1 = CheckCollisionPointPoly(polygon2Vertices[i], polygon1Vertices, 4);
        bool collision2 = CheckCollisionPointPoly(polygon1Vertices[i], polygon2Vertices, 4);

        if (collision1)
        {
            return polygon2Vertices[i];
        }
        else if (collision2)
        {
            return polygon1Vertices[i];
        }
    }

    return Vector2Zero();
}
