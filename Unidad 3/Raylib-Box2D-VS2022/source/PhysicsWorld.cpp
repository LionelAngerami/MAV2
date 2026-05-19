#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
    : world(b2Vec2(0.0f, 39.8f))
{
}

void PhysicsWorld::Step()
{
    world.Step(1.0f / 60.0f, 8, 3);
}

b2World& PhysicsWorld::GetWorld()
{
    return world;
}