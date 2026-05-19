#pragma once

#include "PhysicsObject.h"

class BoxObject : public PhysicsObject
{
private:
    float width;
    float height;

public:
    BoxObject(
        b2World& world,
        Vector2 position,
        float width,
        float height,
        Color color)
    {
        this->width = width;
        this->height = height;
        this->color = color;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);

        body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(width / 2.0f, height / 2.0f);

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1.0f;
        fixture.friction = 0.4f;
        fixture.restitution = 0.2f;

        body->CreateFixture(&fixture);
    }

    void Draw() override
    {
        b2Vec2 pos = body->GetPosition();
        float angle = body->GetAngle() * RAD2DEG;

        Rectangle rect =
        {
            pos.x - width / 2,
            pos.y - height / 2,
            width,
            height
        };

        Vector2 origin = { width / 2, height / 2 };

        DrawRectanglePro(rect, origin, angle, color);
        DrawRectangleLinesEx(rect, 2, DARKBLUE);
    }
};