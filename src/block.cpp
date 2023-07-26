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

sf::Vector2f Block::getPosition() const
{
    return shape->getPosition();
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
    score = 0;
    vanished = true;
}

void Block::make_base(float a_x , float a_y)
{
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(60.0f, 25.0f));
    shape->setPosition(a_x, a_y);
    score_modifer = 0;
    is_explode = 0;
    is_gift = 0;
    is_indestructable = 0;
    score = 0;
}

Block::Block(float a_x, float a_y)
{
    make_base(a_x, a_y);
}

Block::Block(sf::Vector2f a_pos)
{
    make_base(a_pos.x, a_pos.y);
}

bool Block::isExplode() const
{
    return is_explode;
}

bool Block::isGift() const
{
    return is_gift;
}

size_t Block::getScoreValue(size_t a_lvl) const
{
    return score + score * (a_lvl - 1) * score_modifer;
}

bool Block::isIndestructable() const
{
    return is_indestructable;
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

void WhiteBlock::collision()
{
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

void TealBlock::collision()
{
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

void BrownBlock::collision()
{
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

void OrangeBlock::collision()
{
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

void GreenBlock::collision()
{
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

void PurpleBlock::collision()
{
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

void BlueBlock::collision()
{
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

void RedBlock::collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

GrayBlock::GrayBlock(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
    score_modifer = 1;
}

GrayBlock::GrayBlock(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gray-50x.png"))
    shape->setTexture(&(*blockTexture));
    score = 50;
    vanished = false;
    score_modifer = 1;
}

void GrayBlock::collision()
{
    vanish();
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

YellowBlock::YellowBlock(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/yellow-indestructible.png"))
    shape->setTexture(&(*blockTexture));
    is_indestructable = 1;
    score = 0;
    vanished = false;
}

YellowBlock::YellowBlock(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/yellow-indestructible.png"))
    shape->setTexture(&(*blockTexture));
    is_indestructable = 1;
    score = 0;
    vanished = false;
}

void YellowBlock::collision()
{
    score = 0;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

Breakable_Block::Breakable_Block(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/breakable-solid.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    vanished = false;
}

Breakable_Block::Breakable_Block(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/breakable-solid.png"))
    shape->setTexture(&(*blockTexture));
    score = 0; // 300 when broken
    vanished = false;
}

void Breakable_Block::collision()
{
    --break_counter;

    if(break_counter == 0)
    {
        vanish();
        score = 300;
    }
    else
    {
        break_off();
    }
}

void Breakable_Block::break_off()
{
    if(break_counter == 2)
    {
        if(!blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/breakable-broken.png"))
        {   
            throw std::runtime_error("Error: unable to load from file");
        }
    }
}

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

Explodable_Block::Explodable_Block(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/explodable.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    is_explode = 1;
    vanished = false;
}

Explodable_Block::Explodable_Block(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/explodable.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    is_explode = 1;
    vanished = false;
}

void Explodable_Block::collision()
{
    vanish();
}

/* ---------------------------------------------------------------------------------------------------------------------------------------------- */

Gift_Block::Gift_Block(float a_x, float a_y) 
: Block(a_x, a_y)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gift_block.png"))
    shape->setTexture(&(*blockTexture));
    is_gift = true;
    score = 0;
    is_gift = 1;
    vanished = false;
}

Gift_Block::Gift_Block(Vector2f a_vec) 
: Block(a_vec)
{
    blockTexture = std::make_unique<Texture>();
    if(blockTexture->loadFromFile("../../assets/textures/Breakout/PNG/gift_block.png"))
    shape->setTexture(&(*blockTexture));
    score = 0;
    is_gift = 1;
    vanished = false;
}

void Gift_Block::collision()
{
    vanish();
}

}//namespace arkanoid
