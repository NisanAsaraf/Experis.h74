#include "../inc/block.hpp"

namespace arkanoid
{

Block::Block(Color a_color, float a_x, float a_y)
{
    shape = std::make_unique<RectangleShape>(Vector2f(100.0f, 40.0f));
    shape->setFillColor(a_color);
    shape->setPosition(a_x, a_y);
    vanished = false;
}

const RectangleShape& Block::getShape() const
{
    return *shape;
}

FloatRect Block::getGlobalBounds()
{
    return shape->getGlobalBounds();
}

void Block::Collision()
{
    vanish();
}

void Block::vanish()
{
    shape->setPosition(0,0);
    shape->setFillColor(Color::Transparent);
    shape->setSize(Vector2f(0, 0));
}

}//namespace arkanoid
