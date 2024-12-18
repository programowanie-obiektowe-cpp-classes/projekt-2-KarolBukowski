#include "Alien.hpp"

Texture2D            Alien::alien_images[3] = {};
std::vector< Laser > Alien::lasers          = {};
int                  Alien::direction       = 1;

Alien::Alien(int type, Vector2 position) : type{type}, position{position}
{
    if (alien_images[type - 1].id == 0)
    {
        switch (type)
        {
        case 1:
            alien_images[0] = LoadTexture("graphics/alien_1.png");
            break;
        case 2:
            alien_images[1] = LoadTexture("graphics/alien_2.png");
            break;
        case 3:
            alien_images[2] = LoadTexture("graphics/alien_3.png");
            break;
        default:
            alien_images[0] = LoadTexture("graphics/alien_1.png");
            break;
        }
    }

    direction         = 1;
    speed_downward    = 4;
    speed_sideways    = 2;
    laser_speed       = 6;
    laser_firing_rate = 2;
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
    if (GetRandomValue(1, 1000) <= laser_firing_rate)
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

Rectangle Alien::getRect()
{
    return {
        position.x, position.y, float(alien_images[getType() - 1].width), float(alien_images[getType() - 1].height)};
}
