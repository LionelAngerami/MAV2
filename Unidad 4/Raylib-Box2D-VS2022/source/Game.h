#pragma once

#include "PhysicsWorld.h"
#include "Bridge.h"
#include "PlayerBox.h"

class Game
{
private:

    PhysicsWorld* physicsWorld;

    Bridge* bridge;

    PlayerBox* player;

public:

    Game();

    ~Game();

    void Run();

    void Update();

    void Draw();

    void Reset();
};