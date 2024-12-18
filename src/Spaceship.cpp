#include "Spaceship.hpp"

Spaceship::Spaceship()
{
    image          = LoadTexture("graphics/spaceship.png");
    laser_sound    = LoadSound("sounds/laser.ogg");
    position.x     = (GetScreenWidth() - image.width) / 2;
    position.y     = GetScreenHeight() - image.height - 100;
    last_fire_time = 0.0;

    speed             = 7;
    laser_speed       = 6;
    laser_firing_rate = 0.35;
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
    position.x -= speed;
    if (position.x < WINDOW_OFFSET_SIDE__)
    {
        position.x = WINDOW_OFFSET_SIDE__;
    }
}

void Spaceship::MoveRight()
{
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width - WINDOW_OFFSET_SIDE__)
    {
        position.x = GetScreenWidth() - image.width - WINDOW_OFFSET_SIDE__;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - last_fire_time >= laser_firing_rate)
    {
        PlaySound(laser_sound);
        lasers.push_back(
            Laser({position.x + (image.width - Laser::getLaserWidthPixels()) / 2, position.y}, -laser_speed));
        last_fire_time = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

std::vector< Laser >& Spaceship::getLasers()
{
    return lasers;
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - WINDOW_OFFSET_BOT__;
    lasers.clear();
}
