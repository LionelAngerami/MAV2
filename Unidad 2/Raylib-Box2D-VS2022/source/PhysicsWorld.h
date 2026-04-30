#pragma once

#include <box2d.h>

class PhysicsWorld
{
private:
    b2World world;

public:
    PhysicsWorld();

    void Step();

    b2World& GetWorld();
};