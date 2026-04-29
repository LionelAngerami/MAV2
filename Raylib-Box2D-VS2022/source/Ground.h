#pragma once

#include <raylib.h>
#include <box2d.h>

class Ground
{
private:
    b2Body* body;

    float width;
    float height;

    Color color;

public:
    Ground(
        b2World& world,
        Vector2 position,
        float width,
        float height,
        Color color)
    {
        this->width = width;
        this->height = height;
        this->color = color;

        b2BodyDef groundDef;
        groundDef.type = b2_staticBody;
        groundDef.position.Set(position.x, position.y);

        body = world.CreateBody(&groundDef);

        b2PolygonShape shape;
        shape.SetAsBox(width / 2.0f, height / 2.0f);

        body->CreateFixture(&shape, 0.0f);
    }

    void Draw()
    {
        b2Vec2 pos = body->GetPosition();

        DrawRectangle(
            pos.x - width / 2,
            pos.y - height / 2,
            width,
            height,
            color);
    }
};