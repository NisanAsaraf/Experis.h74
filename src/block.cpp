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
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60.0f, 25.0f));
    shape->setPosition(a_x, a_y);
}

Block::Block(sf::Vector2f a_pos) 
{
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60.0f, 25.0f));
    shape->setPosition(a_pos);
}

int Block::getScoreValue(size_t a_lvl) const
{
    return score * a_lvl;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

WhiteBlock::WhiteBlock(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

WhiteBlock::WhiteBlock(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

void WhiteBlock::Collision()
{
    vanish();
}

/* ------------------------ -------------------------------------------------------------------------------------------------------------------- */

TealBlock::TealBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/teal-70.png"))
    shape->setTexture(&(*blockTexture));
    score = 70;
    vanished = false;
}

TealBlock::TealBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/teal-70.png"))
    shape->setTexture(&(*blockTexture));
    score = 70;
    vanished = false;
}

void TealBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

BrownBlock::BrownBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/brown-60.png"))
    shape->setTexture(&(*blockTexture));
    score = 60;
    vanished = false;
}

BrownBlock::BrownBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/brown-60.png"))
    shape->setTexture(&(*blockTexture));
    score = 60;
    vanished = false;
}

void BrownBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

OrangeBlock::OrangeBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/orange-120.png"))
    shape->setTexture(&(*blockTexture));
    score = 120;
    vanished = false;
}

OrangeBlock::OrangeBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/orange-120.png"))
    shape->setTexture(&(*blockTexture));
    score = 120;
    vanished = false;
}

void OrangeBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

GreenBlock::GreenBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/green-80.png"))
    shape->setTexture(&(*blockTexture));
    score = 80;
    vanished = false;
}

GreenBlock::GreenBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/green-80.png"))
    shape->setTexture(&(*blockTexture));
    score = 80;
    vanished = false;
}

void GreenBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

PurpleBlock::PurpleBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/purple-110.png"))
    shape->setTexture(&(*blockTexture));
    score = 110;
    vanished = false;
}

PurpleBlock::PurpleBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/purple-110.png"))
    shape->setTexture(&(*blockTexture));
    score = 110;
    vanished = false;
}

void PurpleBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

BlueBlock::BlueBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/blue-100.png"))
    shape->setTexture(&(*blockTexture));
    score = 100;
    vanished = false;
}

BlueBlock::BlueBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/blue-100.png"))
    shape->setTexture(&(*blockTexture));
    score = 100;
    vanished = false;
}

void BlueBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

RedBlock::RedBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/red-90.png"))
    shape->setTexture(&(*blockTexture));
    score = 90;
    vanished = false;
}

RedBlock::RedBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/red-90.png"))
    shape->setTexture(&(*blockTexture));
    score = 90;
    vanished = false;
}

void RedBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

GrayBlock::GrayBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

GrayBlock::GrayBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

void GrayBlock::Collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

YellowBlock::YellowBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    vanished = false;
}

YellowBlock::YellowBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    vanished = false;
}

void YellowBlock::Collision()
{

}

}//namespace arkanoid
