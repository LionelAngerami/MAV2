#pragma once

class InputManager
{
public:
    float powerX = 3000.0f;
    float powerY = -6000.0f;

    void Update()
    {
        if (IsKeyDown(KEY_RIGHT))
            powerX += 500.0f;

        if (IsKeyDown(KEY_LEFT))
            powerX -= 500.0f;

        if (IsKeyDown(KEY_UP))
            powerY -= 500.0f;

        if (IsKeyDown(KEY_DOWN))
            powerY += 500.0f;
    }
};