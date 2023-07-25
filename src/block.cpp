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

void Block::make_base(float a_x , float a_y)
{
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60.0f, 25.0f));
    shape->setPosition(a_x, a_y);
    if(!soundBuffer.loadFromFile("../../assets/audio/block_collision_sound.ogg"))
    {
        throw std::runtime_error("Error opening sound file");
    }
    collisionSound.setBuffer(soundBuffer);
}

Block::Block(float a_x, float a_y)
{
    make_base(a_x, a_y);
    if(!soundBuffer.loadFromFile("../../assets/audio/block_collision_sound.ogg"))
    {
        throw std::runtime_error("Error opening sound file");
    }
}

Block::Block(sf::Vector2f a_pos)
{
    make_base(a_pos.x, a_pos.y);
}

int Block::getScoreValue(size_t a_lvl) const
{
    return score * a_lvl;
}

void Block::play_collision_sound()
{
    collisionSound.play();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

WhiteBlock::WhiteBlock(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

WhiteBlock::WhiteBlock(Vector2f a_vec)
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

void WhiteBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TealBlock::TealBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/teal-70.png"))
    shape->setTexture(&(*blockTexture));
    score = 70;
    vanished = false;
}

TealBlock::TealBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/teal-70.png"))
    shape->setTexture(&(*blockTexture));
    score = 70;
    vanished = false;
}

void TealBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

BrownBlock::BrownBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/brown-60.png"))
    shape->setTexture(&(*blockTexture));
    score = 60;
    vanished = false;
}

BrownBlock::BrownBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/brown-60.png"))
    shape->setTexture(&(*blockTexture));
    score = 60;
    vanished = false;
}

void BrownBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

OrangeBlock::OrangeBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/orange-120.png"))
    shape->setTexture(&(*blockTexture));
    score = 120;
    vanished = false;
}

OrangeBlock::OrangeBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/orange-120.png"))
    shape->setTexture(&(*blockTexture));
    score = 120;
    vanished = false;
}

void OrangeBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

GreenBlock::GreenBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/green-80.png"))
    shape->setTexture(&(*blockTexture));
    score = 80;
    vanished = false;
}

GreenBlock::GreenBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/green-80.png"))
    shape->setTexture(&(*blockTexture));
    score = 80;
    vanished = false;
}

void GreenBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

PurpleBlock::PurpleBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/purple-110.png"))
    shape->setTexture(&(*blockTexture));
    score = 110;
    vanished = false;
}

PurpleBlock::PurpleBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/purple-110.png"))
    shape->setTexture(&(*blockTexture));
    score = 110;
    vanished = false;
}

void PurpleBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

BlueBlock::BlueBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/blue-100.png"))
    shape->setTexture(&(*blockTexture));
    score = 100;
    vanished = false;
}

BlueBlock::BlueBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/blue-100.png"))
    shape->setTexture(&(*blockTexture));
    score = 100;
    vanished = false;
}

void BlueBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

RedBlock::RedBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/red-90.png"))
    shape->setTexture(&(*blockTexture));
    score = 90;
    vanished = false;
}

RedBlock::RedBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/red-90.png"))
    shape->setTexture(&(*blockTexture));
    score = 90;
    vanished = false;
}

void RedBlock::Collision()
{
    play_collision_sound();
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

GrayBlock::GrayBlock(float a_x, float a_y) : Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

GrayBlock::GrayBlock(Vector2f a_vec) : Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
}

void GrayBlock::Collision()
{
    play_collision_sound();
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
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/white-50.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    vanished = false;
}

void YellowBlock::Collision()
{
    play_collision_sound();
}

}//namespace arkanoid
