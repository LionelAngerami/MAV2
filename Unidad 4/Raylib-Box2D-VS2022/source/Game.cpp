#include "Game.h"

Game::Game()
{
    InitWindow(
        1280,
        720,
        "Puente Colgante"
    );

    SetTargetFPS(60);

    physicsWorld =
        new PhysicsWorld();

    bridge =
        new Bridge(
            physicsWorld->GetWorld()
        );

    player =
        new PlayerBox(
            physicsWorld->GetWorld()
        );
}

Game::~Game()
{
    delete bridge;

    delete player;

    delete physicsWorld;

    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();

        Draw();
    }
}

void Game::Update()
{
    if (IsKeyPressed(KEY_R))
    {
        Reset();
    }

    player->Update();

    physicsWorld->Step();
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    // =====================================================
    // SUELO
    // =====================================================

    DrawRectangle(
        0,
        670,
        1280,
        50,
        DARKGREEN
    );

    // =====================================================
    // OBJETOS
    // =====================================================

    bridge->Draw();

    player->Draw();

    // =====================================================
    // UI
    // =====================================================

    DrawText(
        "PUENTE COLGANTE",
        20,
        20,
        32,
        BLACK
    );

    DrawText(
        "30 eslabones conectados con RevoluteJoint",
        20,
        70,
        20,
        DARKGRAY
    );

    DrawText(
        "3 tensores superiores usando DistanceJoint",
        20,
        100,
        20,
        MAROON
    );

    DrawText(
        "Mover caja: Flechas <- ->",
        20,
        130,
        20,
        DARKBLUE
    );

    DrawText(
        "Reiniciar: R",
        20,
        160,
        20,
        DARKGREEN
    );

    EndDrawing();
}

void Game::Reset()
{
    delete bridge;

    delete player;

    physicsWorld->Reset();

    bridge =
        new Bridge(
            physicsWorld->GetWorld()
        );

    player =
        new PlayerBox(
            physicsWorld->GetWorld()
        );
}