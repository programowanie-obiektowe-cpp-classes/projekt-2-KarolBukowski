#pragma once
#include "Alien.hpp"
#include "Laser.hpp"
#include "Mysteryship.hpp"
#include "Obstacle.hpp"
#include "Spaceship.hpp"
#include "global.h"

class Game
{
private:
    Spaceship               spaceship;
    std::vector< Obstacle > obstacles;
    std::vector< Alien >    aliens;
    Mysteryship             mysteryship;
    Sound                   explosion_sound;

    void DeleteInactiveLasers();
    void CreateObstacles();
    void CreateAliens();
    void MoveAliens();
    void AlienShootLaser();
    void CheckForCollisions();
    void GameOver();
    void Reset();
    void InitGame();
    void CheckForHighscore();
    void SaveHighscoreToFile(int highscore);
    int  LoadHighscoreFromFile();

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
