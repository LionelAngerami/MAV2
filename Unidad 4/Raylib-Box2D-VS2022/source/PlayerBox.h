#pragma once

#include "raylib.h"
#include <box2d.h>

class PlayerBox
{
private:

    b2Body* body;

    Texture2D texture;

    float width;
    float height;

public:

    PlayerBox(b2World& world);

    ~PlayerBox();

    void Update();

    void Draw();
};