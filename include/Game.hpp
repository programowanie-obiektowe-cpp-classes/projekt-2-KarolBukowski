#pragma once
#include "Alien.hpp"
#include "Laser.hpp"
#include "Mysteryship.hpp"
#include "Obstacle.hpp"
#include "Spaceship.hpp"

class Game
{
private:
    Spaceship               spaceship;
    std::vector< Obstacle > obstacles;
    std::vector< Alien >    aliens;
    int                     aliens_direction;
    std::vector< Laser >    alien_lasers;
    constexpr static float  alien_laser_shoot_interval = 0.35;
    float                   time_last_alien_fired;
    Mysteryship             mysteryship;
    float                   mysteryship_spawn_interval;
    float                   time_last_mysteryship_spawned;
    Sound                   explosion_sound;

    void                    DeleteInactiveLasers();
    std::vector< Obstacle > CreateObstacles();
    std::vector< Alien >    CreateAliens();
    void                    MoveAliens();
    void                    MoveDownAliens();
    void                    AlienShootLaser();
    void                    CheckForCollisions();
    void                    GameOver();
    void                    Reset();
    void                    InitGame();
    void                    CheckForHighscore();
    void                    SaveHighscoreToFile(int highscore);
    int                     LoadHighscoreFromFile();

public:
    Game();
    ~Game();

    bool  run;
    int   lives;
    int   score;
    int   highscore;
    Music music;

    void Draw();
    void Update();
    void HandleInput();
};
