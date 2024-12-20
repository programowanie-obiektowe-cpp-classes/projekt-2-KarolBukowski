#pragma once
#include "global.h"
#include <raylib.h>

class Mysteryship
{
private:
    Vector2   position;
    Texture2D image;
    bool      active;
    double    time_last_mysteryship_spawned;
    int       mysteryship_spawn_interval;
    int       direction;
    float     speed;

public:
    Mysteryship();
    ~Mysteryship();

    Mysteryship(const Mysteryship&)            = delete;
    Mysteryship& operator=(const Mysteryship&) = delete;
    Mysteryship(Mysteryship&&)                 = delete;
    Mysteryship& operator=(Mysteryship&&)      = delete;

    void      Update();
    void      Draw();
    void      Spawn();
    void      setStatus(bool status);
    bool      getStatus();
    Rectangle getRect();
};
