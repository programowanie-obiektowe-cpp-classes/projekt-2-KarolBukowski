#pragma once
#include <raylib.h>

class Laser
{
private:
    Vector2 position;
    int     speed;

public:
    Laser(Vector2 position, int speed);

    bool active;

    void      Draw();
    void      Update();
    Rectangle GetRect();
};
