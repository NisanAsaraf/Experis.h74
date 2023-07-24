#include "block.hpp"
namespace arkanoid
{
using namespace sf;

const RectangleShape& Block::getShape() const
{
    return *shape;
}

Vector2f Block::getSize() const
{
    return shape->getSize();
}

FloatRect Block::getGlobalBounds() const
{
    return shape->getGlobalBounds();
}

void Block::Collision()
{
    vanish();
}

bool Block::isVanished() const
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

Block::Block(float a_x, float a_y)
{
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(100.0f, 40.0f));
    shape->setPosition(a_x, a_y);
}

Block::Block(sf::Vector2f a_pos) 
{
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(100.0f, 40.0f));
    shape->setPosition(a_pos);
}

WhiteBlock::WhiteBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    vanished = false;
}

WhiteBlock::WhiteBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    vanished = false;
}

int WhiteBlock::getScoreValue() const
{
    return 50;
}

}//namespace arkanoid
