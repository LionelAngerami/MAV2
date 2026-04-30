#pragma once

#include "PhysicsObject.h"

class CircleObject : public PhysicsObject
{
protected:
    float radius;

public:
    CircleObject(
        b2World& world,
        Vector2 position,
        float radius,
        Color color,
        float restitution = 0.6f)
    {
        this->radius = radius;
        this->color = color;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        body = world.CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = radius;

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1.0f;
        fixture.friction = 0.3f;
        fixture.restitution = restitution;

        body->CreateFixture(&fixture);
    }

    virtual void Draw() override
    {
        b2Vec2 pos = body->GetPosition();

        DrawCircleV({ pos.x, pos.y }, radius, color);
        DrawCircleLines((int)pos.x, (int)pos.y, radius, DARKGRAY);
    }
};