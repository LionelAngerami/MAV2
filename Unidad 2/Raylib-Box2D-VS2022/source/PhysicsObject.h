#pragma once

#include <raylib.h>
#include <box2d.h>

class PhysicsObject
{
protected:
    b2Body* body;
    Color color;

public:
    virtual ~PhysicsObject() = default;

    virtual void Draw() = 0;

    b2Body* GetBody()
    {
        return body;
    }
};