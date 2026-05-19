#pragma once

#include "raylib.h"
#include <box2d.h>

struct PhysicsBox
{
    b2Body* body;

    float width;
    float height;

    Color color;
};

void DrawPhysicsBox(const PhysicsBox& box);