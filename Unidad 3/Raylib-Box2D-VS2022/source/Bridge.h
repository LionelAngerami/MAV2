#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

#include "PhysicsUtils.h"

class Bridge
{
private:

    std::vector<PhysicsBox> segments;

    // =========================
    // ANCLAS LATERALES
    // =========================

    b2Body* leftAnchor;
    b2Body* rightAnchor;

    // =========================
    // PUNTO SUPERIOR ESTÁTICO
    // =========================

    b2Body* topAnchor;

    // =========================
    // PRISMATIC JOINTS
    // =========================

    b2PrismaticJoint* leftPrismatic;
    b2PrismaticJoint* rightPrismatic;

    // =========================
    // DISTANCE JOINT CENTRAL
    // =========================

    b2DistanceJoint* centerSpring;

    // =========================
    // CONFIGURACIÓN
    // =========================

    int segmentCount;

    float segmentWidth;
    float segmentHeight;

    float startX;
    float startY;

    float waveTimer;

public:

    Bridge(b2World& world);

    void Update(float dt);

    void Draw();
};