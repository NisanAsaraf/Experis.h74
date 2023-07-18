#include "../inc/levels.hpp"
#include <memory>

namespace arkanoid
{

void Level_One::setup(size_t row, size_t col)
{

    const int blockWidth = 80;
    const int blockHeight = 30;
    
    const int spacingX = 1;
    const int spacingY = 1;

    blocks.reserve(row * col);

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int x = spacingX + j * (blockWidth + spacingX);
            int y = spacingY + i * (blockHeight + spacingY);

            std::unique_ptr<sf::RectangleShape> block = std::make_unique<sf::RectangleShape>(sf::Vector2f(blockWidth, blockHeight));
            block->setPosition(x, y);
            
            block->setFillColor(sf::Color::Green);
            
            blocks.emplace_back(block);
        }
    }
}

} // namespace arkanoid
