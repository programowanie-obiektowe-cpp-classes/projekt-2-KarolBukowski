#include "Game.hpp"
#include "global.h"
#include <iostream>
#include <raylib.h>
#include <string>

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string score_text    = std::to_string(number);
    int         leading_zeros = width - score_text.length();
    return std::string(leading_zeros, '0') + score_text;
}

int main()
{

    int windowWidth  = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + 2 * WINDOW_OFFSET_SIDE__,
               windowHeight + WINDOW_OFFSET_BOT__ + WINDOW_OFFSET_TOP__,
               "C++ Space Invaders");
    InitAudioDevice();

    Font      font            = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Texture2D spaceship_image = LoadTexture("graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);

        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(GREY__);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18, 20, YELLOW__);
        DrawLineEx({25, 730}, {775, 730}, 3, YELLOW__);
        if (game.getStatus())
        {
            DrawTextEx(
                font, ("LEVEL " + FormatWithLeadingZeros(game.getLevel(), 2)).c_str(), {570, 740}, 34, 2, YELLOW__);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, YELLOW__);
        }
        for (int i = 0; i < game.getLives(); i++)
        {
            float pos_x = 50 + 50 * i;
            DrawTextureV(spaceship_image, {pos_x, 745}, WHITE);
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, YELLOW__);
        DrawTextEx(font, FormatWithLeadingZeros(game.getScore(), 5).c_str(), {50, 40}, 34, 2, YELLOW__);

        DrawTextEx(font, "HIGHSCORE", {570, 15}, 34, 2, YELLOW__);
        DrawTextEx(font, FormatWithLeadingZeros(game.getHighscore(), 5).c_str(), {655, 40}, 34, 2, YELLOW__);

        game.Draw();

        EndDrawing();
    }

    UnloadTexture(spaceship_image);

    CloseWindow();
    CloseAudioDevice();
    return 0;
}