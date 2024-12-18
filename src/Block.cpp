#include "Block.hpp"

Block::Block(Vector2 position) : position{position}
{}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, block_size_pixels, block_size_pixels, YELLOW__);
}

Rectangle Block::getRect()
{
    return {position.x, position.y, block_size_pixels, block_size_pixels};
}

int Block::getBlockSizePixels()
{
    return block_size_pixels;
}
