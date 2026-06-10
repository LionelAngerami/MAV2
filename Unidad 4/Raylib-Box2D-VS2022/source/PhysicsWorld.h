#pragma once

#include <box2d.h>

class PhysicsWorld
{
private:

    b2World* world;

    b2Body* ground;

public:

    PhysicsWorld();

    ~PhysicsWorld();

    void Step();

    void Reset();

    b2World& GetWorld();
};