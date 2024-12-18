#pragma once
#include "global.h"
#include <raylib.h>

class Block
{
private:
    Vector2 position;

    // Static constants
    constexpr static int block_size_pixels = 3;

public:
    Block(Vector2 position);

    void       Draw();
    Rectangle  getRect();
    static int getBlockSizePixels();
};
