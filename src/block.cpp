#include "block.hpp"
namespace arkanoid
{
using namespace sf;

Block::Block(Texture a_blockTexture, float a_x, float a_y)
{
    shape = std::make_unique<RectangleShape>(Vector2f(100.0f, 40.0f));
    blockTexture = std::make_unique<Texture>(a_blockTexture);
    shape->setTexture(&(*blockTexture));
    shape->setPosition(a_x, a_y);
    vanished = false;
}

const RectangleShape& Block::getShape() const
{
    return *shape;
}

Vector2f Block::getSize()
{
    return shape->getSize();
}

FloatRect Block::getGlobalBounds()
{
    return shape->getGlobalBounds();
}

void Block::Collision()
{
    vanish();
}

bool Block::isVanished()
{
    return vanished;
}

void Block::vanish()
{
    shape->setPosition(0,0);
    shape->setFillColor(Color::Transparent);
    shape->setSize(Vector2f(0, 0));
    vanished = true;
}

}//namespace arkanoid
