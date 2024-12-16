#include "Game.hpp"
#include <iostream>
#include <raylib.h>
#include <string>

std::string FromatWithLeadingZeros(int number, int width)
{
    std::string score_text    = std::to_string(number);
    int         leading_zeros = width - score_text.length();
    return std::string(leading_zeros, '0') + score_text;
}

int main()
{
    Color grey         = {29, 29, 27, 255};
    Color yellow       = {243, 216, 63, 255};
    int   offset       = 50;
    int   windowWidth  = 750;
    int   windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    Font      font            = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceship_image = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);

        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18, 20, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if (game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }
        for (int i = 0; i < game.lives; i++)
        {
            float pos_x = 50 + 50 * i;
            DrawTextureV(spaceship_image, {pos_x, 745}, WHITE);
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        DrawTextEx(font, FromatWithLeadingZeros(game.score, 5).c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGHSCORE", {570, 15}, 34, 2, yellow);
        DrawTextEx(font, FromatWithLeadingZeros(game.highscore, 5).c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();

        EndDrawing();
    }

    UnloadTexture(spaceship_image);

    CloseWindow();
    CloseAudioDevice();
    return 0;
}