#include "DifficultyManager.hpp"

DifficultyManager::DifficultyManager()
    : alien_speed_downward{6.5},
      alien_speed_sideways{1.5},
      alien_laser_speed{6},
      alien_laser_firing_rate{14},

      spaceship_speed{7},
      spaceship_laser_speed{6},
      spaceship_laser_firing_rate{0.35}
{}

void DifficultyManager::IncreaseDifficulty()
{
    alien_speed_downward += 1.5;
    alien_speed_sideways += 0.5;
    alien_laser_speed += 0.75;
    alien_laser_firing_rate += 7;

    spaceship_speed -= 0.5;
    spaceship_laser_speed -= 0.5;
    spaceship_laser_firing_rate += 0.05;
}

float DifficultyManager::getAlienSpeedDownward() const
{
    return alien_speed_downward;
}

float DifficultyManager::getAlienSpeedSideways() const
{
    return alien_speed_sideways;
}

float DifficultyManager::getAlienLaserSpeed() const
{
    return alien_laser_speed;
}

int DifficultyManager::getAlienLaserFiringRate() const
{
    return alien_laser_firing_rate;
}

float DifficultyManager::getSpaceshipSpeed() const
{
    return spaceship_speed;
}

float DifficultyManager::getSpaceshipLaserSpeed() const
{
    return spaceship_laser_speed;
}

double DifficultyManager::getSpaceshipLaserFiringRate() const
{
    return spaceship_laser_firing_rate;
}
