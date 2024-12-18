#pragma once
#include "global.h"
#include <raylib.h>

class Laser
{
private:
    Vector2 position;
    int     speed;

    // Static constants
    constexpr static int laser_width_pixels  = 3;
    constexpr static int laser_height_pixels = 15;

public:
    Laser(Vector2 position, int speed);

    bool active;

    void      Draw();
    void      Update();
    Rectangle getRect();

    static int getLaserWidthPixels();
    static int getLaserHeightPixels();
};
