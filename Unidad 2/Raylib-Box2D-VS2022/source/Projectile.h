#pragma once

#include "CircleObject.h"

class Projectile : public CircleObject
{
public:
    Projectile(
        b2World& world,
        Vector2 position)
        :
        CircleObject(world, position, 15.0f, RED, 0.8f)
    {
    }

    void Launch(float forceX, float forceY)
    {
        b2Vec2 impulse(forceX, forceY);
        body->ApplyLinearImpulseToCenter(impulse, true);
    }
};