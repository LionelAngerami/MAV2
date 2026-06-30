#include "Game.h"

Game::Game()
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Disparo Parabolico"
    );

    SetTargetFPS(60);

    world = new b2World(
        b2Vec2(0.0f, 25.0f)
    );

    world->SetContactListener(&listener);

    CreateGround();

    projectile = new Projectile(*world);

    CreateTargets();

    score = 0;

    win = false;
}

Game::~Game()
{
    for (Target* target : targets)
        delete target;

    delete projectile;

    delete world;

    CloseWindow();
}

void Game::CreateGround()
{
    b2BodyDef groundDef;

    groundDef.type = b2_staticBody;

    groundDef.position.Set(
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT - 20.0f
    );

    ground = world->CreateBody(&groundDef);

    b2PolygonShape shape;

    shape.SetAsBox(
        SCREEN_WIDTH / 2.0f,
        20.0f
    );

    ground->CreateFixture(
        &shape,
        0.0f
    );
}

void Game::CreateTargets()
{
    targets.push_back(
        new Target(
            *world,
            SCREEN_WIDTH * 0.55,
            520));

    targets.push_back(
        new Target(
            *world,
            SCREEN_WIDTH * 0.4,
            480));

    targets.push_back(
        new Target(
            *world,
            SCREEN_WIDTH * 0.8,
            460));
}

void Game::Reset()
{
    for (Target* target : targets)
        delete target;

    targets.clear();

    delete projectile;

    delete world;

    world = new b2World(
        b2Vec2(0.0f, 25.0f));

    CreateGround();

    projectile =
        new Projectile(*world);

    CreateTargets();

    score = 0;

    win = false;

    listener.Reset();

    world->SetContactListener(&listener);
}

void Game::Update()
{
    if (IsKeyPressed(KEY_R))
    {
        Reset();
        return;
    }

    projectile->Update();

    world->Step(
        1.0f / 60.0f,
        8,
        3);

    if (projectile->IsLaunched())
    {  
        if (score >= 3)
        {
            win = true;
        }

        b2Vec2 pos =
            projectile->GetBody()->GetPosition();

        if (pos.x > SCREEN_WIDTH + 100 ||
            pos.y > SCREEN_HEIGHT + 100)
        {
            projectile->Reset();
        }
    }

    score = listener.GetScore();

    if (score >= 3)
        win = true;
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //------------------------------------
    // Piso
    //------------------------------------

    DrawRectangle(
        0,
        SCREEN_HEIGHT - 40,
        SCREEN_WIDTH,
        40,
        DARKGREEN);

    //------------------------------------
    // Dianas
    //------------------------------------

    for (Target* target : targets)
    {
        target->Draw();
    }

    //------------------------------------
    // Proyectil
    //------------------------------------

    projectile->Draw();

    //------------------------------------
    // Interfaz
    //------------------------------------

    ui.Draw(
        projectile->GetAngle(),
        projectile->GetPower(),
        score,
        win);

    EndDrawing();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();

        Draw();
    }
}