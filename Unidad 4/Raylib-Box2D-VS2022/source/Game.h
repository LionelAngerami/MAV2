#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "Projectile.h"
#include "Target.h"
#include "UI.h"
#include "ContactListener.h"

class Game
{
private:

    static const int SCREEN_WIDTH = 600;
    static const int SCREEN_HEIGHT = 600;

    ContactListener listener;

    b2World* world;


    b2Body* ground;

    Projectile* projectile;

    std::vector<Target*> targets;

    UI ui;

    int score;

    bool win;

    void CreateGround();

    void CreateTargets();

    void Reset();

public:

    Game();

    ~Game();

    void Run();

    void Update();

    void Draw();
};