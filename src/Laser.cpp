#include "Laser.hpp"

Laser::Laser(Vector2 position, int speed) : position{position}, speed{speed}, active{true}
{}

void Laser::Draw()
{
    if (active)
    {
        DrawRectangle(position.x, position.y, laser_width_pixels, laser_height_pixels, YELLOW__);
    }
}

void Laser::Update()
{
    position.y += speed;
    if (active)
    {
        if (position.y > GetScreenHeight() - WINDOW_OFFSET_BOT__ || position.y < WINDOW_OFFSET_TOP__)
        {
            active = false;
        }
    }
}

void Laser::setStatus(bool status)
{
    active = status;
}

bool Laser::getStatus()
{
    return active;
}

Rectangle Laser::getRect()
{
    return {position.x, position.y, laser_width_pixels, laser_height_pixels};
}

int Laser::getLaserWidthPixels()
{
    return laser_width_pixels;
}

int Laser::getLaserHeightPixels()
{
    return laser_height_pixels;
}
