#include "Bridge.h"

Bridge::Bridge(b2World& world)
{
    segmentCount = 25;

    segmentWidth = 25.0f;
    segmentHeight = 12.0f;

    // =====================================================
    // DISTANCIA ENTRE ANCLAS
    // MÁS CORTA QUE EL PUENTE
    // PARA GENERAR "PANCEO"
    // =====================================================

    float leftX = 180.0f;
    float rightX = 1200.0f;

    float startY = 520.0f;

    // =====================================================
    // ANCLAS FIJAS
    // =====================================================

    b2BodyDef anchorDef;
    anchorDef.type = b2_staticBody;

    // izquierda

    anchorDef.position.Set(leftX, startY);

    leftAnchor =
        world.CreateBody(&anchorDef);

    // derecha

    anchorDef.position.Set(rightX, startY);

    rightAnchor =
        world.CreateBody(&anchorDef);

    // =====================================================
    // SEGMENTOS DEL PUENTE
    // =====================================================

    float totalBridgeLength =
        segmentCount * segmentWidth;

    float spacing =
        (rightX - leftX)
        / (float)(segmentCount);

    b2Body* previousBody =
        leftAnchor;

    for (int i = 0; i < segmentCount; i++)
    {
        b2BodyDef segmentDef;

        segmentDef.type =
            b2_dynamicBody;

        // MÁS LARGO QUE LA DISTANCIA REAL
        // para que se curve

        segmentDef.position.Set(
            leftX + i * spacing,
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
        fixtureDef.friction = 0.8f;
        fixtureDef.restitution = 0.0f;

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
                leftX +
                i * spacing
                - spacing / 2.0f,
                startY
            )
        );

        world.CreateJoint(&revoluteDef);

        previousBody = segmentBody;
    }

    // =====================================================
    // CONECTAR ÚLTIMO SEGMENTO
    // =====================================================

    b2RevoluteJointDef endJoint;

    endJoint.Initialize(
        previousBody,
        rightAnchor,
        b2Vec2(
            rightX,
            startY
        )
    );

    world.CreateJoint(&endJoint);

    // =====================================================
    // ANCLAS SUPERIORES
    // =====================================================

    b2BodyDef topDef;
    topDef.type = b2_staticBody;

    // izquierda

    topDef.position.Set(
        leftX + 220.0f,
        startY - 220.0f
    );

    topAnchor1 =
        world.CreateBody(&topDef);

    // centro

    topDef.position.Set(
        (leftX + rightX) / 2.0f,
        startY - 250.0f
    );

    topAnchor2 =
        world.CreateBody(&topDef);

    // derecha

    topDef.position.Set(
        rightX - 220.0f,
        startY - 220.0f
    );

    topAnchor3 =
        world.CreateBody(&topDef);

    // =====================================================
    // DISTANCE JOINTS
    // =====================================================

    int leftIndex = (segmentCount / 4);
    int centerIndex = (segmentCount / 2);
    int rightIndex = (segmentCount / 4) * 3;

    b2DistanceJointDef springDef;

    // ================= LEFT =================

    springDef.Initialize(
        topAnchor1,
        segments[leftIndex].body,
        topAnchor1->GetPosition(),
        segments[leftIndex].body->GetPosition()
    );

    leftSpring =
        (b2DistanceJoint*)
        world.CreateJoint(&springDef);

    // ================= CENTER =================

    springDef.Initialize(
        topAnchor2,
        segments[centerIndex].body,
        topAnchor2->GetPosition(),
        segments[centerIndex].body->GetPosition()
    );

	centerSpring =
		(b2DistanceJoint*)
        world.CreateJoint(&springDef);

    // ================= RIGHT =================

    springDef.Initialize(
        topAnchor3,
        segments[rightIndex].body,
        topAnchor3->GetPosition(),
        segments[rightIndex].body->GetPosition()
    );

    rightSpring =
        (b2DistanceJoint*)
        world.CreateJoint(&springDef);
}

void Bridge::Draw()
{
    // =====================================================
    // DIBUJAR RESORTES
    // =====================================================

    int leftIndex = (segmentCount / 4);
    int centerIndex = (segmentCount / 2);
    int rightIndex = (segmentCount / 4) * 3;

    DrawLine(
        (int)topAnchor1->GetPosition().x,
        (int)topAnchor1->GetPosition().y,
        (int)segments[leftIndex]
        .body->GetPosition().x,
        (int)segments[leftIndex]
        .body->GetPosition().y,
        RED
    );

    DrawLine(
        (int)topAnchor2->GetPosition().x,
        (int)topAnchor2->GetPosition().y,
        (int)segments[centerIndex]
        .body->GetPosition().x,
        (int)segments[centerIndex]
        .body->GetPosition().y,
        RED
    );

    DrawLine(
        (int)topAnchor3->GetPosition().x,
        (int)topAnchor3->GetPosition().y,
        (int)segments[rightIndex]
        .body->GetPosition().x,
        (int)segments[rightIndex]
        .body->GetPosition().y,
        RED
    );

    // =====================================================
    // DIBUJAR JOINTS
    // =====================================================

    for (int i = 0;
        i < segmentCount -1;
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
            (posA.x ),
            (posA.y )
        };

        DrawCircleV(
            jointPos,
            4.0f,
            BLACK
        );
    }

    // =====================================================
    // DIBUJAR SEGMENTOS
    // =====================================================

    for (const auto& segment : segments)
    {
        DrawPhysicsBox(segment);
    }

    // =====================================================
    // ANCLAS LATERALES
    // =====================================================

    DrawCircle(
        (int)leftAnchor->GetPosition().x-segmentWidth,
        (int)leftAnchor->GetPosition().y,
        10.0f,
        BLUE
    );

    DrawCircle(
        (int)rightAnchor->GetPosition().x-segmentWidth,
        (int)rightAnchor->GetPosition().y,
        10.0f,
        BLUE
    );

    // =====================================================
    // ANCLAS SUPERIORES
    // =====================================================

    DrawCircle(
        (int)topAnchor1->GetPosition().x,
        (int)topAnchor1->GetPosition().y,
        8.0f,
        RED
    );

    DrawCircle(
        (int)topAnchor2->GetPosition().x,
        (int)topAnchor2->GetPosition().y,
        8.0f,
        RED
    );

    DrawCircle(
        (int)topAnchor3->GetPosition().x,
        (int)topAnchor3->GetPosition().y,
        8.0f,
        RED
    );
}