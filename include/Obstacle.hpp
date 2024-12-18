#pragma once
#include "Block.hpp"
#include "global.h"
#include <vector>

class Obstacle
{
private:
    Vector2              position;
    std::vector< Block > blocks;

    static std::vector< std::vector< int > > grid;

public:
    Obstacle(Vector2 position);

    void Draw();

    std::vector< Block >&                    getBlocks();
    static std::vector< std::vector< int > > getGrid();
};
