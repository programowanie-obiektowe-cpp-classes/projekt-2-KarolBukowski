#pragma once
#include "DifficultyManager.hpp"
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
    static float  speed;
    static float  laser_speed;
    static double laser_firing_rate;

public:
    Spaceship();
    ~Spaceship();

    Spaceship(const Spaceship&)            = delete;
    Spaceship& operator=(const Spaceship&) = delete;
    Spaceship(Spaceship&&)                 = delete;
    Spaceship& operator=(Spaceship&&)      = delete;

    void                  Draw();
    void                  MoveLeft();
    void                  MoveRight();
    void                  FireLaser();
    void                  Reset();
    Rectangle             getRect();
    std::vector< Laser >& getLasers();
    static void           ApplyDifficulty(const DifficultyManager& difficulty);
};
