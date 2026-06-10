#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "PhysicsUtils.h"

class Bridge
{
private:

    std::vector<PhysicsBox> segments;

    b2Body* leftAnchor;
    b2Body* rightAnchor;

    b2Body* topAnchor1;
    b2Body* topAnchor2;
    b2Body* topAnchor3;

    int segmentCount;

    float segmentWidth;
    float segmentHeight;

    b2DistanceJoint* centerSpring;
    b2DistanceJoint* leftSpring;
    b2DistanceJoint* rightSpring;

public:

    Bridge(b2World& world);

    void Draw();
};