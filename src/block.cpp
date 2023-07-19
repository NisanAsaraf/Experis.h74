#include "../inc/block.hpp"

namespace arkanoid
{

Block::Block(Color a_color, float a_x, float a_y)
{
    shape = std::make_unique<RectangleShape>(Vector2f(20.0f, 20.0f));
    shape->setFillColor(a_color);
    shape->setPosition(a_x, a_y);
    vanished = false;
}

RectangleShape& Block::operator*()
{
    return *shape;
}

FloatRect Block::getGlobalBounds()
{
    return shape->getGlobalBounds();
}

void Block::vanish()
{
    shape->setPosition(0,0);
    shape->setFillColor(Color::Transparent);
    shape->setSize(Vector2f(0, 0));
}

}//namespace arkanoid
