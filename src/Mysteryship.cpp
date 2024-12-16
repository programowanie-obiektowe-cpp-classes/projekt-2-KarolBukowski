#include "Mysteryship.hpp"

Mysteryship::Mysteryship()
{
    image  = LoadTexture("Graphics/mystery.png");
    active = false;
}

Mysteryship::~Mysteryship()
{
    UnloadTexture(image);
}

void Mysteryship::Update()
{
    if (active)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25)
        {
            active = false;
        }
    }
}

void Mysteryship::Draw()
{
    if (active)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void Mysteryship::Spawn()
{
    position.y = 90;
    int side   = GetRandomValue(0, 1);
    if (side == 0)
    {
        position.x = 25;
        speed      = 3;
    }
    else
    {
        position.y = GetScreenWidth() - image.width - 25;
        speed      = -3;
    }
    active = true;
}

Rectangle Mysteryship::GetRect()
{
    if (active)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {position.x, position.y, 0, 0};
    }
}
