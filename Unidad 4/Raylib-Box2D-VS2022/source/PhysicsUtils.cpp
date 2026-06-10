#include "PhysicsUtils.h"

void DrawPhysicsBox(const PhysicsBox& box)
{
    b2Vec2 pos = box.body->GetPosition();

    float angle =
        box.body->GetAngle() * RAD2DEG;

    Rectangle rect =
    {
        pos.x - box.width / 2.0f,
        pos.y - box.height / 2.0f,
        box.width,
        box.height
    };

    Vector2 origin =
    {
        box.width / 2.0f,
        box.height / 2.0f
    };

    DrawRectanglePro(
        rect,
        origin,
        angle,
        box.color
    );
}