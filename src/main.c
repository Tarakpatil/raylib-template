#include "raylib.h"
#include <math.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

typedef struct {
    float x, y, z;
} Vec3;

Vec3 rotateX(Vec3 p, float angle) {
    float rad = angle * DEG2RAD;
    float c = cosf(rad);
    float s = sinf(rad);

    return (Vec3) {
        p.x,
        p.y * c - p.z * s,
        p.y * s + p.z * c
    };
}

Vec3 rotateY(Vec3 p, float angle) {
    float rad = angle * DEG2RAD;
    float c = cosf(rad);
    float s = sinf(rad);

    return (Vec3) {
         p.x * c + p.z * s,
         p.y,
        -p.x * s + p.z * c
    };
}

Vec3 rotateZ(Vec3 p, float angle) {
    float rad = angle * DEG2RAD;
    float c = cosf(rad);
    float s = sinf(rad);

    return (Vec3) {
        p.x * c - p.y * s,
        p.x * s + p.y * c,
        p.z
    };
}

Vector2 project(Vec3 p, float distance) {
    float z = p.z + distance;
    if (z < 0.1f) z = 0.1f;

    float scale = distance / z;

    return (Vector2) {
        SCREEN_WIDTH  / 2.0f + p.x * scale * 100.0f,
        SCREEN_HEIGHT / 2.0f - p.y * scale * 100.0f
    };
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "rotation");
    SetTargetFPS(60);

    Vec3 vertices[8] = {
        {-1, -1, -1}, { 1, -1, -1},
        { 1,  1, -1}, {-1,  1, -1},
        {-1, -1,  1}, { 1, -1,  1},
        { 1,  1,  1}, {-1,  1,  1}
    };

    int edges[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };

    float angleX = 0.0f;
    float angleY = 0.0f;
    // float angleZ = 0.0f;
    Color color = {237, 135, 237};

    while (!WindowShouldClose()) {

        angleX += 0.8f;
        angleY += 1.2f;
        // angleZ += 2.2f;

        BeginDrawing();
            ClearBackground(color);

            Vector2 projected[8];
            for (int i = 0; i < 8; i++)
            {
                Vec3 p = vertices[i];

                p = rotateX(p, angleX);
                p = rotateY(p, angleY);
                // p = rotateZ(p, angleZ);
                p.z += 4.0f;

                projected[i] = project(p, 3.0f);
            }

            for (int i = 0; i < 12; i++)
            {
                Vector2 a = projected[edges[i][0]];
                Vector2 b = projected[edges[i][1]];
                DrawLineEx(a, b, 2.0f, BLACK);
            }

            for (int i = 0; i < 8; i++)
            {
                DrawCircleV(projected[i], 4.0f, RED);
            }

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
