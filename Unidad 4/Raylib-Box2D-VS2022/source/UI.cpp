#include "UI.h"
#include "raylib.h"

void UI::Draw(
    float angle,
    float power,
    int score,
    bool win)
{
    DrawRectangle(
        10,
        10,
        350,
        150,
        Fade(BLACK, 0.20f));

    DrawText(
        TextFormat("Angulo : %.0f", angle),
        20,
        30,
        10,
        BLACK);

    DrawText(
        TextFormat("Impulso : %.1f", power),
        20,
        50,
        10,
        BLACK);

    DrawText(
        TextFormat("Puntos : %i / 3", score),
        20,
        70,
        10,
        RED);


    DrawText(
        "Flechas: ajustar disparo",
        20,
        90,
        10,
        BLACK);

    DrawText(
        "ESPACIO: disparar",
        20,
        110,
        10,
        BLACK);

    DrawText(
        "R: Reiniciar",
        20,
        130,
        10,
        BLACK);

    if (win)
    {
        DrawRectangle(
            20,
            220,
            520,
            120,
            Fade(GREEN, 0.30f));

        DrawText(
            "¡¡GANASTE!!",
            220,
            245,
            40,
            DARKGREEN);
    }
}