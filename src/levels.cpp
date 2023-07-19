#include "../inc/levels.hpp"
#include <memory>
#include <iostream>

namespace arkanoid
{

Level_One::Level_One(size_t row, size_t col)
{
    std::vector<sf::Color> block_colors;

    block_colors.push_back(sf::Color::Green);
    block_colors.push_back(sf::Color::Magenta);
    block_colors.push_back(sf::Color::Cyan);

    const int blockWidth = 100;
    const int blockHeight = 40;
    
    const int spacingX = 1;
    const int spacingY = 1;

    blocks.reserve(row * col);
    
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            int x = 150 + spacingX + j * (blockWidth + spacingX);
            int y = 100 + spacingY + i * (blockHeight + spacingY);
            Color brick_color = block_colors.at(i);

            std::unique_ptr<Block> block = std::make_unique<Block>(brick_color, x, y);
            blocks.emplace_back(std::move(block)); 
        }
    }
}

void Level_One::reset()
{
    blocks.clear();
}

std::vector<std::unique_ptr<Block>>& Level_One::get_blocks()
{
    return blocks;
}

} // namespace arkanoid
