#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>

struct PhysicsBox
{
    b2Body* body;
    float width;
    float height;
    Color color;
};

struct PhysicsCircle
{
    b2Body* body;
    float radius;
    Color color;
};

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Bienvenida");
    SetTargetFPS(60);

    Color fondo = { 110, 100, 215, 255 };
    Color textoPrincipal = RAYWHITE;
    Color textoSecundario = DARKPURPLE;
    Color sueloColor = Fade(DARKGREEN, 0.7f);

    // Mundo físico
    b2Vec2 gravity(0.0f, 39.8f);
    b2World world(gravity);

    // -----------------------------
    // Suelo estático
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
    b2Body* groundBody = world.CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
    groundBody->CreateFixture(&groundShape, 0.0f);

    std::vector<PhysicsBox> boxes;
    std::vector<PhysicsCircle> circles;

    // -----------------------------
    // Crear algunas cajas dinámicas
    // -----------------------------
    for (int i = 0; i < 4; i++)
    {
        b2BodyDef boxDef;
        boxDef.type = b2_dynamicBody;
        boxDef.position.Set(300.0f + i * 80.0f, 80.0f + i * 20.0f);

        b2Body* boxBody = world.CreateBody(&boxDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox(25.0f, 25.0f);

        b2FixtureDef boxFixture;
        boxFixture.shape = &boxShape;
        boxFixture.density = 1.0f;
        boxFixture.friction = 0.4f;
        boxFixture.restitution = 0.2f;

        boxBody->CreateFixture(&boxFixture);

        boxes.push_back({ boxBody, 50.0f, 50.0f, Fade(SKYBLUE, 0.95f) });
    }

    // -----------------------------
    // Crear algunos círculos dinámicos
    // -----------------------------
    for (int i = 0; i < 3; i++)
    {
        b2BodyDef circleDef;
        circleDef.type = b2_dynamicBody;
        circleDef.position.Set(650.0f + i * 60.0f, 60.0f + i * 30.0f);

        b2Body* circleBody = world.CreateBody(&circleDef);

        b2CircleShape circleShape;
        circleShape.m_radius = 20.0f;

        b2FixtureDef circleFixture;
        circleFixture.shape = &circleShape;
        circleFixture.density = 1.0f;
        circleFixture.friction = 0.3f;
        circleFixture.restitution = 0.6f;

        circleBody->CreateFixture(&circleFixture);

        circles.push_back({ circleBody, 20.0f, Fade(ORANGE, 0.95f) });
    }

    // -----------------------------
    // Proyectil (catapulta)
    // -----------------------------
        b2BodyDef projectileDef;
        projectileDef.type = b2_dynamicBody;
        projectileDef.position.Set(150.0f, screenHeight - 100.0f);

        b2Body* projectileBody = world.CreateBody(&projectileDef);

        b2CircleShape projectileShape;
        projectileShape.m_radius = 15.0f;

        b2FixtureDef projectileFixture;
        projectileFixture.shape = &projectileShape;
        projectileFixture.density = 1.0f;
        projectileFixture.friction = 0.3f;
        projectileFixture.restitution = 0.8f;

        projectileBody->CreateFixture(&projectileFixture);

        PhysicsCircle projectile = { projectileBody, 15.0f, RED };

		float powerX = 3000.0f; // Dirección horizontal
		float powerY = -6000.0f; // Potencia del impulso

    while (!WindowShouldClose())
    {

        // -----------------------------
        // INPUT
        // -----------------------------

        if (IsKeyDown(KEY_RIGHT))
        {
            powerX += 500.0f; // Apuntar a la derecha
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            powerX += -500.0f; // Apuntar a la izquierda
		}

        if (IsKeyDown(KEY_UP))
        {
            powerY += -500.0f; // Aumentar potencia
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            powerY += 500.0f; // Disminuir potencia
		}

        // Aplicar impulso con ESPACIO
        if (IsKeyPressed(KEY_SPACE))
        {
            b2Vec2 impulso(powerX, powerY); 
            projectile.body->ApplyLinearImpulseToCenter(impulso, true);
        }

        ////--------------------------

        // Avanzar simulación
        world.Step(1.0f / 60.0f, 8, 3);

        BeginDrawing();
        ClearBackground(fondo);

        // Suelo visual
        DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);

        // Dibujar cajas
        for (const auto& box : boxes)
        {
            b2Vec2 pos = box.body->GetPosition();
            float angle = box.body->GetAngle() * RAD2DEG;

            Rectangle rect = {
                pos.x - box.width / 2.0f,
                pos.y - box.height / 2.0f,
                box.width,
                box.height
            };

            Vector2 origin = { box.width / 2.0f, box.height / 2.0f };
            DrawRectanglePro(rect, origin, angle, box.color);
            DrawRectangleLinesEx(rect, 2, DARKBLUE);
        }

        // Dibujar círculos
        for (const auto& circle : circles)
        {
            b2Vec2 pos = circle.body->GetPosition();
            DrawCircleV({ pos.x, pos.y }, circle.radius, circle.color);
            DrawCircleLines((int)pos.x, (int)pos.y, circle.radius, BROWN);
        }

        // Dibujar proyectil
        b2Vec2 posProj = projectile.body->GetPosition();
        DrawCircleV({ posProj.x, posProj.y }, projectile.radius, projectile.color);
        DrawCircleLines((int)posProj.x, (int)posProj.y, projectile.radius, DARKGRAY);

        // -----------------------------
        // UI
        // -----------------------------

        DrawRectangle(90, 70, 820, 120, Fade(BLACK, 0.18f));
        DrawText("ESPACIO: Impulsar", 120, 90, 22, textoPrincipal);
        DrawText(TextFormat("Flechas < -->: Fuerza Horizontal           X:%1.0f", powerX/100), 120, 120, 20, YELLOW);
        DrawText(TextFormat("Flechas Up / Down: Fuerza Vertical      Y:%1.0f", powerY/-100), 120, 150, 20, YELLOW);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}