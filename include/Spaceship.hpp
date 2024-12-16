#pragma once
#include "Laser.hpp"
#include <raylib.h>
#include <vector>

class Spaceship
{
private:
    Texture2D image;
    Vector2   position;
    double    last_fire_time;
    Sound     laser_sound;

public:
    Spaceship();
    ~Spaceship();

    std::vector< Laser > lasers;

    void      Draw();
    void      MoveLeft();
    void      MoveRight();
    void      FireLaser();
    Rectangle GetRect();
    void      Reset();
};
