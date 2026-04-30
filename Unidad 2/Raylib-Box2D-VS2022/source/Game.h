#pragma once

#include <vector>
#include <memory>

#include "PhysicsWorld.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Projectile.h"
#include "InputManager.h"
#include "Ground.h"

class Game
{
private:
    const int screenWidth = 1000;
    const int screenHeight = 600;

    PhysicsWorld physicsWorld;

    std::vector<BoxObject> boxes;
    std::vector<CircleObject> circles;
    std::unique_ptr<Ground> ground;

    std::unique_ptr<Projectile> projectile;

    InputManager input;

public:
    Game();

    void Run();

private:
    void Initialize();
    void Update();
    void Draw();
};