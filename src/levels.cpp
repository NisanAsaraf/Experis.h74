#include "../inc/levels.hpp"
#include <memory>

namespace arkanoid
{

Level_One::Level_One(size_t row, size_t col)
{
    std::vector<sf::Color> block_colors;

    block_colors.push_back(sf::Color::Green);
    block_colors.push_back(sf::Color::Magenta);
    block_colors.push_back(sf::Color::Cyan);
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
            int x = spacingX + j * (blockWidth + spacingX);
            int y = spacingY + i * (blockHeight + spacingY);
            sf::Color brick_color = block_colors.at(j);

            std::unique_ptr<sf::RectangleShape> block = std::make_unique<sf::RectangleShape>(sf::Vector2f(blockWidth, blockHeight));
            block->setPosition(x, y);
            
            block->setFillColor(brick_color);
            
            blocks.emplace_back(std::move(block)); 
        }
    }
}

std::vector<std::unique_ptr<sf::RectangleShape>> const& Level_One::operator*()
{
    return blocks;
}

std::vector<std::unique_ptr<sf::RectangleShape>> const& Level_One::get_blocks()
{
    return blocks;
}

} // namespace arkanoid
