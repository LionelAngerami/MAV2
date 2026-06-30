#pragma once
#pragma once

#include <box2d.h>

class ContactListener :
    public b2ContactListener
{
private:

    int score;

public:

    ContactListener();

    void BeginContact(
        b2Contact* contact) override;

    int GetScore() const;

    void Reset();
};