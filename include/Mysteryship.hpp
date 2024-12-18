#pragma once
#include "global.h"
#include <raylib.h>

class Mysteryship
{
private:
    Vector2   position;
    Texture2D image;
    double    time_last_mysteryship_spawned;
    int       mysteryship_spawn_interval;
    int       direction;

    // Difficulty-dependent variables
    int speed;

public:
    Mysteryship();
    ~Mysteryship();

    bool active;

    void      Update();
    void      Draw();
    void      Spawn();
    Rectangle getRect();
};
