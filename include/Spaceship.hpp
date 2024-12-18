#pragma once
#include "Laser.hpp"
#include "global.h"
#include <raylib.h>
#include <vector>

class Spaceship
{
private:
    Texture2D            image;
    Sound                laser_sound;
    Vector2              position;
    double               last_fire_time;
    std::vector< Laser > lasers;

    // Difficulty-dependent variables
    int    speed;
    int    laser_speed;
    double laser_firing_rate;

public:
    Spaceship();
    ~Spaceship();

    void                  Draw();
    void                  MoveLeft();
    void                  MoveRight();
    void                  FireLaser();
    void                  Reset();
    Rectangle             getRect();
    std::vector< Laser >& getLasers();
};
