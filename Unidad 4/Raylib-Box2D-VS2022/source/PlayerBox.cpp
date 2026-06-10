#include "PlayerBox.h"

PlayerBox::PlayerBox(b2World& world)
{
    width = 50.0f;
    height = 50.0f;

    texture = LoadTexture("assets/box.png");

    b2BodyDef bodyDef;

    bodyDef.type =
        b2_dynamicBody;

    bodyDef.position.Set(
        220.0f,
        350.0f
    );

    body =
        world.CreateBody(&bodyDef);

    b2PolygonShape shape;

    shape.SetAsBox(
        width / 2.0f,
        height / 2.0f
    );

    b2FixtureDef fixture;

    fixture.shape = &shape;

    fixture.density = 8.0f;

    fixture.friction = 1.0f;

    fixture.restitution = 0.0f;

    body->CreateFixture(&fixture);
}

PlayerBox::~PlayerBox()
{
    UnloadTexture(texture);
}

void PlayerBox::Update()
{
    // =====================================
    // MOVIMIENTO
    // =====================================

    if (IsKeyDown(KEY_RIGHT))
    {
        body->ApplyForceToCenter(
            b2Vec2(3000000.0f, 0.0f),
            true
        );
    }

    if (IsKeyDown(KEY_LEFT))
    {
        body->ApplyForceToCenter(
            b2Vec2(-3000000.0f, 0.0f),
            true
        );
    }
}

void PlayerBox::Draw()
{
    b2Vec2 pos =
        body->GetPosition();

    float angle =
        body->GetAngle() * RAD2DEG;

    Rectangle source =
    {
        0,
        0,
        (float)texture.width,
        (float)texture.height
    };

    Rectangle dest =
    {
        pos.x,
        pos.y,
        width,
        height
    };

    Vector2 origin =
    {
        width / 2.0f,
        height / 2.0f
    };

    DrawTexturePro(
        texture,
        source,
        dest,
        origin,
        angle,
        WHITE
    );
}