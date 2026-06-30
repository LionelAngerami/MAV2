#include "Projectile.h"
#include "BodyData.h"

BodyData bodyData;

Projectile::Projectile(b2World& physicsWorld)
{
    world = &physicsWorld;

    radius = 15.0f;

    angle = 45.0f;

    power = 25.0f;

    launched = false;

    CreateBody();

}

void Projectile::CreateBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(50.0f, 550.0f);

    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.2f;
    fixture.restitution = 0.8f;

    body->CreateFixture(&fixture);

    body->SetGravityScale(1.0f);

    bodyData.type = BodyType::Projectile;
    bodyData.owner = this;

    body->GetUserData().pointer =
        reinterpret_cast<uintptr_t>(&bodyData);
}

void Projectile::Update()
{
    if (launched)
        return;

    if (IsKeyDown(KEY_LEFT))
        angle += 1.0f;

    if (IsKeyDown(KEY_RIGHT))
        angle -= 1.0f;

    if (IsKeyDown(KEY_UP))
        power += 0.2f;

    if (IsKeyDown(KEY_DOWN))
        power -= 0.2f;

    if (power < 5.0f)
        power = 5.0f;

    if (power > 60.0f)
        power = 60.0f;

    if (angle < 5)
        angle = 5;

    if (angle > 75)
        angle = 75;

    if (IsKeyPressed(KEY_SPACE))
    {
        Launch();
    }
}

void Projectile::Launch()
{
    launched = true;

    float radians = angle * DEG2RAD;

    b2Vec2 impulse(
        cosf(radians) * power*2500,
        -sinf(radians) * power*2500
    );

    body->ApplyLinearImpulseToCenter(
        impulse,
        true
    );
}

void Projectile::Reset()
{
    world->DestroyBody(body);

    launched = false;

    CreateBody();
}

void Projectile::Draw()
{
    b2Vec2 pos = body->GetPosition();

    DrawCircleV(
        { pos.x, pos.y },
        radius,
        RED
    );

    if (!launched)
    {
        float r = angle * DEG2RAD;

        Vector2 end =
        {
            pos.x + cosf(r) * power * 2,
            pos.y - sinf(r) * power * 2
        };

        DrawLineEx(
            { pos.x,pos.y },
            end,
            3,
            DARKGREEN
        );
    }
}

bool Projectile::IsLaunched() const
{
    return launched;
}

b2Body* Projectile::GetBody()
{
    return body;
}

float Projectile::GetAngle() const
{
    return angle;
}

float Projectile::GetPower() const
{
    return power;
}