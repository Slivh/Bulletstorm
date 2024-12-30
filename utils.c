#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "game.h"

void GetRotatedRecCorners(Vector2 *corners, Rectangle rec, float angle) {
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

Vector2 vectorPerpendicular(Vector2 v) {
    return (Vector2){-v.y, v.x};
}

void projectPolygon(Polygon polygon, Vector2 axis, float *min, float *max) {
    float projection = Vector2DotProduct(polygon.vertices[0], axis);
    *min = *max = projection;

    for (int i = 1; i < polygon.vertexCount; i++) {
        projection = Vector2DotProduct(polygon.vertices[i], axis);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}

bool overlapOnAxis(Polygon a, Polygon b, Vector2 axis) {
    float minA, maxA, minB, maxB;
    projectPolygon(a, axis, &minA, &maxA);
    projectPolygon(b, axis, &minB, &maxB);

    return !(maxA < minB || maxB < minA);
}

bool checkCollision(Polygon a, Polygon b) {
    for (int i = 0; i < a.vertexCount; i++) {
        Vector2 edge = Vector2Subtract(a.vertices[(i + 1) % a.vertexCount], a.vertices[i]);
        Vector2 axis = vectorPerpendicular(edge);

        if (!overlapOnAxis(a, b, axis)) {
            return false;
        }
    }

    for (int i = 0; i < b.vertexCount; i++) {
        Vector2 edge = Vector2Subtract(b.vertices[(i + 1) % b.vertexCount], b.vertices[i]);
        Vector2 axis = vectorPerpendicular(edge);

        if (!overlapOnAxis(a, b, axis)) {
            return false;
        }
    }

    return true;
}

bool CheckCollisionRotatedRecs(Rectangle rectangle1, float angle1, Rectangle rectangle2, float angle2) {

    Vector2 polygon1Vertices[4];
    Vector2 polygon2Vertices[4];

    GetRotatedRecCorners(polygon1Vertices, rectangle1, angle1);
    GetRotatedRecCorners(polygon2Vertices, rectangle2, angle2);

    Polygon polygon1 = {polygon1Vertices, 4};
    Polygon polygon2 = {polygon2Vertices, 4};

    if (checkCollision(polygon1, polygon2)) {
        return true;
    } else {
        return false;
    }
}
