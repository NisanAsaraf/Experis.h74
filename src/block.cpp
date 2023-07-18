#include "../inc/block.hpp"

namespace arkanoid
{

Block::Block(sf::Color a_color, float a_x, float a_y)
{
    block = std::make_unique<sf::RectangleShape>(sf::Vector2f(20.0f, 20.0f));
    block->setFillColor(a_color);
    block->setPosition(a_x, a_y);
}

sf::RectangleShape& Block::operator*()
{
    return *block;
}

}//namespace arkanoid
