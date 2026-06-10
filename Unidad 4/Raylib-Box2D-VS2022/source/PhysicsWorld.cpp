#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{
    world =
        new b2World(
            b2Vec2(0.0f, 20.0f)
        );

    // =====================================
    // SUELO
    // =====================================

    b2BodyDef groundDef;

    groundDef.type =
        b2_staticBody;

    groundDef.position.Set(
        640.0f,
        690.0f
    );

    ground =
        world->CreateBody(&groundDef);

    b2PolygonShape groundShape;

    groundShape.SetAsBox(
        640.0f,
        20.0f
    );

    ground->CreateFixture(
        &groundShape,
        0.0f
    );
}

PhysicsWorld::~PhysicsWorld()
{
    delete world;
}

void PhysicsWorld::Step()
{
    world->Step(
        1.0f / 60.0f,
        8,
        3
    );
}

void PhysicsWorld::Reset()
{
    delete world;

    world =
        new b2World(
            b2Vec2(0.0f, 20.0f)
        );

    // recrear suelo

    b2BodyDef groundDef;

    groundDef.type =
        b2_staticBody;

    groundDef.position.Set(
        640.0f,
        690.0f
    );

    ground =
        world->CreateBody(&groundDef);

    b2PolygonShape groundShape;

    groundShape.SetAsBox(
        640.0f,
        20.0f
    );

    ground->CreateFixture(
        &groundShape,
        0.0f
    );
}

b2World& PhysicsWorld::GetWorld()
{
    return *world;
}