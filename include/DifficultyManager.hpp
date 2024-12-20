#ifndef DIFFICULTY_MANAGER_HPP
#define DIFFICULTY_MANAGER_HPP
#include "global.h"
#include <raylib.h>

class DifficultyManager
{
private:
    float alien_speed_downward;
    float alien_speed_sideways;
    float alien_laser_speed;
    int   alien_laser_firing_rate;

    float  spaceship_speed;
    float  spaceship_laser_speed;
    double spaceship_laser_firing_rate;

public:
    DifficultyManager();

    void IncreaseDifficulty();

    float getAlienSpeedDownward() const;
    float getAlienSpeedSideways() const;
    float getAlienLaserSpeed() const;
    int   getAlienLaserFiringRate() const;

    float  getSpaceshipSpeed() const;
    float  getSpaceshipLaserSpeed() const;
    double getSpaceshipLaserFiringRate() const;
};
#endif