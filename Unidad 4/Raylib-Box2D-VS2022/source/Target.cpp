#include "Target.h"

Target::Target(
    b2World& world,
    float x,
    float y)
{
    size = 40.0f;

    destroyed = false;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);

    body = world.CreateBody(&bodyDef);

    //------------------------------------
    // Forma
    //------------------------------------

    b2PolygonShape shape;
    shape.SetAsBox(
        size / 2.0f,
        size / 2.0f);

    //------------------------------------
    // Fixture SENSOR
    //------------------------------------

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);

    //------------------------------------
    // User Data
    //------------------------------------

    bodyData.type = BodyType::Target;
    bodyData.owner = this;

    body->GetUserData().pointer =
        reinterpret_cast<uintptr_t>(&bodyData);
}

void Target::Draw()
{
    if (destroyed)
        return;

    b2Vec2 pos = body->GetPosition();

    Rectangle rect =
    {
        pos.x - size / 2.0f,
        pos.y - size / 2.0f,
        size,
        size
    };

    DrawRectangleRec(
        rect,
        BLUE);

    DrawRectangleLinesEx(
        rect,
        2,
        DARKBLUE);

    DrawLine(
        (int)(pos.x - size / 2),
        (int)pos.y,
        (int)(pos.x + size / 2),
        (int)pos.y,
        SKYBLUE);

    DrawLine(
        (int)pos.x,
        (int)(pos.y - size / 2),
        (int)pos.x,
        (int)(pos.y + size / 2),
        SKYBLUE);
}

void Target::Destroy()
{
    destroyed = true;
}

bool Target::IsDestroyed() const
{
    return destroyed;
}

b2Body* Target::GetBody()
{
    return body;
}