#pragma once

#include "raylib.h"
#include <box2d.h>

class Projectile
{
private:

    b2World* world;

    b2Body* body;

    float radius;

    float angle;

    float power;

    bool launched;

    void CreateBody();

public:

    Projectile(b2World& world);

    void Update();

    void Draw();

    void Launch();

    void Reset();

    bool IsLaunched() const;

    b2Body* GetBody();

    float GetAngle() const;

    float GetPower() const;
};