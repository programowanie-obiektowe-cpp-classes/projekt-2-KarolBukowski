#pragma once
#include <raylib.h>

class Alien
{
private:
    int type;

public:
    Alien(int type, Vector2 position);

    static Texture2D alien_images[3];
    Vector2          position;

    static void UnloadImages();
    void        Update(int direction);
    void        Draw();
    int         GetType();
    Rectangle   GetRect();
};