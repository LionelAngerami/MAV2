#pragma once

#include "raylib.h"
#include <box2d.h>
#include "BodyData.h"

class Target
{
private:

    b2Body* body;

    float size;

    bool active;

public:

    Target(
        b2World& world,
        float x,
        float y
    );

    void Draw();

    bool IsActive() const;

    BodyData bodyData;

    bool destroyed;

    void Destroy();

    bool IsDestroyed() const;

    b2Body* GetBody();
};