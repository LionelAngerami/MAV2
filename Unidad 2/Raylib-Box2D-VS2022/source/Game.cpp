#include "Game.h"
#include <raylib.h>

Game::Game()
{
    InitWindow(screenWidth, screenHeight, "MAV2: Unidad 2");
    SetTargetFPS(60);

    Initialize();
}

void Game::Initialize()
{
    b2World& world = physicsWorld.GetWorld();

    ground = std::make_unique<Ground>(
        world,
        Vector2{ screenWidth / 2.0f, screenHeight - 40.0f },
        (float)screenWidth,
        40.0f,
        Fade(DARKGREEN, 0.7f));

    for (int i = 0; i < 4; i++)
    {
        boxes.push_back(
            BoxObject(
                world,
                Vector2{ 300.0f + i * 80.0f, 80.0f + i * 20.0f },
                50,
                50,
                SKYBLUE));
    }

    for (int i = 0; i < 3; i++)
    {
        circles.push_back(
            CircleObject(
                world,
                Vector2{ 650.0f + i * 60.0f, 60.0f + i * 30.0f },
                20,
                ORANGE));
    }

    projectile = std::make_unique<Projectile>(
        world,
        Vector2{ 150.0f, 500.0f });
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    CloseWindow();
}

void Game::Update()
{
    input.Update();

    if (IsKeyPressed(KEY_SPACE))
    {
        projectile->Launch(input.powerX, input.powerY);
    }

    physicsWorld.Step();
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground({ 110,100,215,255 });

    ground->Draw();

    for (auto& box : boxes)
        box.Draw();

    for (auto& circle : circles)
        circle.Draw();

    projectile->Draw();

    DrawText("ESPACIO: Impulsar", 120, 90, 22, RAYWHITE);
    DrawText(TextFormat("Flechas < -->: Fuerza Horizontal           X:%1.0f", input.powerX / 100), 120, 120, 20, YELLOW);
    DrawText(TextFormat("Flechas Up / Down: Fuerza Vertical      Y:%1.0f", input.powerY / -100), 120, 150, 20, YELLOW);

    EndDrawing();
}