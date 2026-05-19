#include "Bridge.h"
#include <cmath>

Bridge::Bridge(b2World& world)
{
    segmentCount = 25;

    segmentWidth = 40.0f;
    segmentHeight = 12.0f;

    startX = 140.0f;
    startY = 500.0f;

    waveTimer = 0.0f;

    // =====================================================
    // CUERPO ESTÁTICO AUXILIAR
    // =====================================================

    b2BodyDef staticDef;
    staticDef.type = b2_staticBody;
    staticDef.position.Set(0.0f, 0.0f);

    b2Body* staticBody =
        world.CreateBody(&staticDef);

    // =====================================================
    // ANCLA IZQUIERDA
    // =====================================================

    b2BodyDef leftDef;
    leftDef.type = b2_dynamicBody;

    leftDef.position.Set(
        startX - 50.0f,
        startY
    );

    leftAnchor =
        world.CreateBody(&leftDef);

    b2CircleShape anchorShape;
    anchorShape.m_radius = 12.0f;

    b2FixtureDef anchorFixture;
    anchorFixture.shape = &anchorShape;
    anchorFixture.density = 5.0f;

    leftAnchor->CreateFixture(&anchorFixture);

    // =====================================================
    // ANCLA DERECHA
    // =====================================================

    b2BodyDef rightDef;
    rightDef.type = b2_dynamicBody;

    rightDef.position.Set(
        startX + segmentCount * segmentWidth,
        startY
    );

    rightAnchor =
        world.CreateBody(&rightDef);

    rightAnchor->CreateFixture(&anchorFixture);

    // =====================================================
    // PRISMATIC JOINT IZQUIERDO
    // =====================================================

    b2PrismaticJointDef leftPrismaticDef;

    leftPrismaticDef.Initialize(
        staticBody,
        leftAnchor,
        leftAnchor->GetPosition(),
        b2Vec2(0.0f, 1.0f)
    );

    leftPrismaticDef.enableLimit = false;

    leftPrismaticDef.lowerTranslation = -800.0f;
    leftPrismaticDef.upperTranslation = 800.0f;

    leftPrismaticDef.enableMotor = true;
    leftPrismaticDef.maxMotorForce = 5000000.0f;

    leftPrismatic =
        (b2PrismaticJoint*)
        world.CreateJoint(&leftPrismaticDef);

    // =====================================================
    // PRISMATIC JOINT DERECHO
    // =====================================================

    b2PrismaticJointDef rightPrismaticDef;

    rightPrismaticDef.Initialize(
        staticBody,
        rightAnchor,
        rightAnchor->GetPosition(),
        b2Vec2(1.0f, 0.0f)
    );

    rightPrismaticDef.enableLimit = true;

    rightPrismaticDef.lowerTranslation = -300.0f;
    rightPrismaticDef.upperTranslation = 300.0f;

    rightPrismaticDef.enableMotor = true;
    rightPrismaticDef.maxMotorForce = 500000.0f;

    rightPrismatic =
        (b2PrismaticJoint*)
        world.CreateJoint(&rightPrismaticDef);

    // =====================================================
    // CREAR SEGMENTOS
    // =====================================================

    b2Body* previousBody = leftAnchor;

    for (int i = 0; i < segmentCount; i++)
    {
        b2BodyDef segmentDef;

        segmentDef.type =
            b2_dynamicBody;

        segmentDef.position.Set(
            startX + i * segmentWidth,
            startY
        );

        b2Body* segmentBody =
            world.CreateBody(&segmentDef);

        b2PolygonShape segmentShape;

        segmentShape.SetAsBox(
            segmentWidth / 2.0f,
            segmentHeight / 2.0f
        );

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &segmentShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.7f;
        fixtureDef.restitution = 0.1f;

        segmentBody->CreateFixture(
            &fixtureDef
        );

        PhysicsBox box;

        box.body = segmentBody;
        box.width = segmentWidth;
        box.height = segmentHeight;
        box.color = BROWN;

        segments.push_back(box);

        // =================================================
        // REVOLUTE JOINT
        // =================================================

        b2RevoluteJointDef revoluteDef;

        revoluteDef.Initialize(
            previousBody,
            segmentBody,
            b2Vec2(
                startX +
                (i - 0.5f) * segmentWidth,
                startY
            )
        );

        world.CreateJoint(&revoluteDef);

        previousBody = segmentBody;
    }

    // =====================================================
    // CONECTAR ÚLTIMO SEGMENTO
    // =====================================================

    b2RevoluteJointDef endRevolute;

    endRevolute.Initialize(
        previousBody,
        rightAnchor,
        b2Vec2(
            startX +
            (segmentCount - 0.5f)
            * segmentWidth,
            startY
        )
    );

    world.CreateJoint(&endRevolute);

    // =====================================================
    // ANCLA SUPERIOR
    // =====================================================

    b2BodyDef topDef;

    topDef.type = b2_staticBody;

    topDef.position.Set(
        startX +
        (segmentCount * segmentWidth) / 2.0f,
        startY - 180.0f
    );

    topAnchor =
        world.CreateBody(&topDef);

    // =====================================================
    // DISTANCE JOINT CENTRAL
    // =====================================================

    int centerIndex =
        segmentCount / 2;

    b2DistanceJointDef distanceDef;

    distanceDef.Initialize(
        topAnchor,
        segments[centerIndex].body,
        topAnchor->GetPosition(),
        segments[centerIndex].body->GetPosition()
    );

    // comportamiento elástico

    distanceDef.stiffness = 2.0f;
    distanceDef.damping = 0.2f;

    centerSpring =
        (b2DistanceJoint*)
        world.CreateJoint(&distanceDef);
}

void Bridge::Update(float dt)
{
    waveTimer += dt;

    float speed =
        sinf(waveTimer * 2.0f)
        * 35.0f;

    leftPrismatic->SetMotorSpeed(speed);

    rightPrismatic->SetMotorSpeed(-speed);
}

void Bridge::Draw()
{
    // =====================================================
    // RESORTE CENTRAL
    // =====================================================

    b2Vec2 topPos =
        topAnchor->GetPosition();

    int centerIndex =
        segmentCount / 2;

    b2Vec2 centerPos =
        segments[centerIndex]
        .body->GetPosition();

    DrawLine(
        (int)topPos.x,
        (int)topPos.y,
        (int)centerPos.x,
        (int)centerPos.y,
        RED
    );

    // =====================================================
    // REVOLUTE JOINTS
    // =====================================================

    for (int i = 0;
        i < segmentCount - 1;
        i++)
    {
        b2Vec2 posA =
            segments[i]
            .body->GetPosition();

        b2Vec2 posB =
            segments[i + 1]
            .body->GetPosition();

        DrawLine(
            (int)posA.x,
            (int)posA.y,
            (int)posB.x,
            (int)posB.y,
            DARKGRAY
        );

        Vector2 jointPos =
        {
            (posA.x + posB.x - segmentWidth) / 2.0f,
            (posA.y + posB.y) / 2.0f
        };

        DrawCircleV(
            jointPos,
            5.0f,
            BLACK
        );
    }

    // =====================================================
    // SEGMENTOS
    // =====================================================

    for (const auto& segment : segments)
    {
        DrawPhysicsBox(segment);
    }

    // =====================================================
    // ANCLAS LATERALES
    // =====================================================

    Vector2 leftPos =
    {
        leftAnchor->GetPosition().x,
        leftAnchor->GetPosition().y
    };

    Vector2 rightPos =
    {
        rightAnchor->GetPosition().x - segmentWidth,
        rightAnchor->GetPosition().y
    };

    DrawCircleV(leftPos, 12.0f, BLUE);
    DrawCircleV(rightPos, 12.0f, BLUE);

    DrawCircleLines(
        (int)leftPos.x,
        (int)leftPos.y,
        12.0f,
        WHITE
    );

    DrawCircleLines(
        (int)rightPos.x,
        (int)rightPos.y,
        12.0f,
        WHITE
    );

    // =====================================================
    // ANCLA SUPERIOR
    // =====================================================

    DrawCircle(
        (int)topPos.x,
        (int)topPos.y,
        10.0f,
        RED
    );
}