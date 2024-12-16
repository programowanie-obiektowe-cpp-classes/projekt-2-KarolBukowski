#include "Alien.hpp"

Texture2D Alien::alien_images[3] = {};

Alien::Alien(int type, Vector2 position) : type{type}, position{position}
{
    if (alien_images[type - 1].id == 0)
    {
        switch (type)
        {
        case 1:
            alien_images[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alien_images[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alien_images[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default:
            alien_images[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}

void Alien::UnloadImages()
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alien_images[i]);
    }
}

void Alien::Update(int direction)
{
    position.x += direction;
}

void Alien::Draw()
{
    DrawTextureV(alien_images[type - 1], position, WHITE);
}

int Alien::GetType()
{
    return type;
}

Rectangle Alien::GetRect()
{
    return {
        position.x, position.y, float(alien_images[GetType() - 1].width), float(alien_images[GetType() - 1].height)};
}
