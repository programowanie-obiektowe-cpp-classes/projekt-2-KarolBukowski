#include "Alien.hpp"

Texture2D            Alien::alien_images[3]   = {};
std::vector< Laser > Alien::lasers            = {};
int                  Alien::direction         = 1;
float                Alien::speed_downward    = 0.0f;
float                Alien::speed_sideways    = 0.0f;
float                Alien::laser_speed       = 0.0f;
int                  Alien::laser_firing_rate = 0;

Alien::Alien(int type, Vector2 position) : type{type}, position{position}
{}

void Alien::LoadImages()
{
    alien_images[0] = LoadTexture("graphics/alien_1.png");
    alien_images[1] = LoadTexture("graphics/alien_2.png");
    alien_images[2] = LoadTexture("graphics/alien_3.png");
}

void Alien::UnloadImages()
{
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(alien_images[i]);
    }
}

void Alien::MoveSideways()
{
    position.x += direction * speed_sideways;
}

void Alien::MoveDownward()
{
    position.y += speed_downward;
}

void Alien::ChangeDirection()
{
    direction *= -1;
}

void Alien::FireLaser()
{
    if (GetRandomValue(1, 10000) <= laser_firing_rate)
    {
        lasers.push_back(Laser(
            {position.x + (alien_images[type - 1].width - Laser::getLaserWidthPixels()) / 2, position.y}, laser_speed));
    }
}

void Alien::Draw()
{
    DrawTextureV(alien_images[type - 1], position, WHITE);
}

int Alien::getType()
{
    return type;
}

Vector2 Alien::getPosition()
{
    return position;
}

std::vector< Laser >& Alien::getLasers()
{
    return lasers;
}

void Alien::ApplyDifficulty(const DifficultyManager& difficulty)
{
    speed_downward    = difficulty.getAlienSpeedDownward();
    speed_sideways    = difficulty.getAlienSpeedSideways();
    laser_speed       = difficulty.getAlienLaserSpeed();
    laser_firing_rate = difficulty.getAlienLaserFiringRate();
}

Rectangle Alien::getRect()
{
    return {
        position.x, position.y, float(alien_images[getType() - 1].width), float(alien_images[getType() - 1].height)};
}
