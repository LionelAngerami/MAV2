#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>

#include "Bridge.h"

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 700;

    InitWindow(
        screenWidth,
        screenHeight,
        "Puente Colgante - Box2D + Raylib"
    );

    SetTargetFPS(60);

    // =====================================================
    // MUNDO FÍSICO
    // =====================================================

    b2Vec2 gravity(0.0f, 20.0f);

    b2World world(gravity);

    // =====================================================
    // PUENTE
    // =====================================================

    Bridge bridge(world);

    while (!WindowShouldClose())
    {
        // =================================================
        // UPDATE
        // =================================================

        bridge.Update(1.0f / 60.0f);

        world.Step(
            1.0f / 60.0f,
            8,
            3
        );

        // =================================================
        // DRAW
        // =================================================

        BeginDrawing();

        ClearBackground(SKYBLUE);
       
        // puente

        bridge.Draw();

        // UI

        DrawText(
            "PUENTE COLGANTE",
            20,
            20,
            30,
            BLACK
        );

        DrawText(
            "Revolute Joint + Distance Joint + Prismatic Joint",
            20,
            60,
            20,
            DARKGRAY
        );

        DrawText(
            "Los anclajes laterales generan ondas verticales",
            20,
            90,
            20,
            DARKBLUE
        );

        DrawText(
            "El centro posee un resorte que estabiliza el puente",
            20,
            120,
            20,
            MAROON
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}