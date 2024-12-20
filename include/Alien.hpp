#pragma once
#include "DifficultyManager.hpp"
#include "Laser.hpp"
#include "global.h"
#include <raylib.h>
#include <vector>

class Alien
{
private:
    Vector2 position;
    int     type;

    static std::vector< Laser > lasers;
    static int                  direction;

    // Difficulty-dependent variables
    static float speed_downward;
    static float speed_sideways;
    static float laser_speed;
    static int   laser_firing_rate;

public:
    Alien(int type, Vector2 position);

    static Texture2D alien_images[3];

    static void                  LoadImages();
    static void                  UnloadImages();
    void                         MoveSideways();
    void                         MoveDownward();
    static void                  ChangeDirection();
    void                         FireLaser();
    void                         Draw();
    Rectangle                    getRect();
    int                          getType();
    Vector2                      getPosition();
    static std::vector< Laser >& getLasers();
    static void                  ApplyDifficulty(const DifficultyManager& difficulty);
};