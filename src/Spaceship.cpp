#include "Spaceship.hpp"

Spaceship::Spaceship()
{
    image          = LoadTexture("Graphics/spaceship.png");
    position.x     = (GetScreenWidth() - image.width) / 2;
    position.y     = GetScreenHeight() - image.height - 100;
    last_fire_time = 0.0;
    laser_sound    = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
    UnloadSound(laser_sound);
}

void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 7;
    if (position.x < 25)
    {
        position.x = 0;
    }
}

void Spaceship::MoveRight()
{
    position.x += 7;
    int right_boundary = GetScreenWidth() - image.width;
    if (position.x > right_boundary - 25)
    {
        position.x = right_boundary;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - last_fire_time >= 0.35)
    {
        PlaySound(laser_sound);
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
        last_fire_time = GetTime();
    }
}

Rectangle Spaceship::GetRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
