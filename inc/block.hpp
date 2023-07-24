#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "abs_block.hpp"

namespace arkanoid
{
class WhiteBlock : public Block // 50 score
{
public:
    WhiteBlock(float a_x , float a_y);
    WhiteBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class TealBlock : public Block // 70 score
{
public:
    TealBlock(float a_x , float a_y);
    TealBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class BrownBlock : public Block // 60 score
{
public:   
    BrownBlock(float a_x , float a_y);
    BrownBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class OrangeBlock : public Block // 120 score
{
public:
    OrangeBlock(float a_x , float a_y);
    OrangeBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class GreenBlock : public Block // 80 score
{
public:
    GreenBlock(float a_x , float a_y);
    GreenBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class PurpleBlock : public Block // 110 score
{
public:
    PurpleBlock(float a_x , float a_y);
    PurpleBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class BlueBlock : public Block // 100 score
{
public:
    BlueBlock(float a_x , float a_y);
    BlueBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class GrayBlock : public Block // 50 score
{
public:
    GrayBlock(float a_x , float a_y);
    GrayBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class RedBlock : public Block // 90
{
public:
    RedBlock(float a_x , float a_y);
    RedBlock(sf::Vector2f a_pos);
    void Collision() override;
};


class YellowBlock : public Block // indestructible
{
public:
    YellowBlock(float a_x , float a_y);
    YellowBlock(sf::Vector2f a_pos);
    void Collision() override;
};

}//namespace arkanoid
#endif //BLOCK_H