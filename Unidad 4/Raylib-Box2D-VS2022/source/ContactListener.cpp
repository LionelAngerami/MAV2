#include "ContactListener.h"

#include "BodyData.h"

#include "Target.h"

ContactListener::ContactListener()
{
    score = 0;
}

void ContactListener::BeginContact(
    b2Contact* contact)
{
    BodyData* a =
        (BodyData*)contact
        ->GetFixtureA()
        ->GetBody()
        ->GetUserData().pointer;

    BodyData* b =
        (BodyData*)contact
        ->GetFixtureB()
        ->GetBody()
        ->GetUserData().pointer;

    if (!a || !b)
        return;

    bool hit =

        (a->type == BodyType::Projectile &&
            b->type == BodyType::Target)

        ||

        (b->type == BodyType::Projectile &&
            a->type == BodyType::Target);

    if (!hit)
        return;

    BodyData* targetData =

        a->type == BodyType::Target ?
        a : b;

    Target* target =
        (Target*)targetData->owner;

    if (target->IsDestroyed())
        return;

    target->Destroy();

    score++;
}

int ContactListener::GetScore() const
{
    return score;
}

void ContactListener::Reset()
{
    score = 0;
}