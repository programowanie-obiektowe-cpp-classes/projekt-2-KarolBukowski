#include "Mysteryship.hpp"

Mysteryship::Mysteryship() : active{false}, speed{2.5}
{
    image                         = LoadTexture("graphics/mystery.png");
    time_last_mysteryship_spawned = GetTime();
    mysteryship_spawn_interval    = GetRandomValue(10, 20);
}

Mysteryship::~Mysteryship()
{
    UnloadTexture(image);
}

void Mysteryship::Update()
{
    if (active)
    {
        position.x += direction * speed;
        if (position.x > GetScreenWidth() - image.width - WINDOW_OFFSET_SIDE__ || position.x < WINDOW_OFFSET_SIDE__)
        {
            active = false;
        }
    }
    else if (GetTime() - time_last_mysteryship_spawned > mysteryship_spawn_interval)
    {
        Spawn();
        time_last_mysteryship_spawned = GetTime();
        mysteryship_spawn_interval    = GetRandomValue(10, 20);
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
        position.x = WINDOW_OFFSET_SIDE__;
        direction  = 1;
    }
    else
    {
        position.x = GetScreenWidth() - image.width - WINDOW_OFFSET_SIDE__;
        direction  = -1;
    }
    active = true;
}

void Mysteryship::setStatus(bool status)
{
    active = status;
}

bool Mysteryship::getStatus()
{
    return active;
}

Rectangle Mysteryship::getRect()
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
