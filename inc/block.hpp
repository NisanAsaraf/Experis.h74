#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{
/* class Block
{
public:
    Block(sf::Texture a_texture, float a_x, float a_y);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getSize();
    const sf::RectangleShape& getShape() const;
    bool isVanished();
    void Collision() ;
private:
    void vanish();
private:
    std::unique_ptr<sf::RectangleShape> shape;
    std::unique_ptr<sf::Texture> blockTexture;
    bool vanished;

}; */

class Block
{
public:
    Block(float a_x, float a_y);
    Block(sf::Vector2f a_pos);
    virtual ~Block() = default;

    virtual int getScoreValue() const = 0;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getSize() const ;
    const sf::RectangleShape& getShape() const;
    bool isVanished() const ;
    void Collision();
private:
    void vanish();
protected:
    std::unique_ptr<sf::RectangleShape> shape;
    std::unique_ptr<sf::Texture> blockTexture;
    bool vanished;
};

class WhiteBlock : public Block // 50 score
{
public:
    WhiteBlock(float a_x , float a_y);
    WhiteBlock(sf::Vector2f a_pos);
    int getScoreValue() const override;
};

class TealBlock : Block // 70 score
{
    TealBlock(float a_x , float a_y);
    TealBlock(sf::Vector2f a_pos);
};

class BrownBlock : Block // 60 score
{
    BrownBlock(float a_x , float a_y);
    BrownBlock(sf::Vector2f a_pos);
};

class OrangeBlock : Block // 120 score
{
    OrangeBlock(float a_x , float a_y);
    OrangeBlock(sf::Vector2f a_pos);
};

class GreenBlock : Block // 80 score
{
    GreenBlock(float a_x , float a_y);
    GreenBlock(sf::Vector2f a_pos);
};

class PurpleBlock : Block // 110 score
{
    PurpleBlock(float a_x , float a_y);
    PurpleBlock(sf::Vector2f a_pos);
};

class BlueBlock : Block // 100 score
{
    BlueBlock(float a_x , float a_y);
    BlueBlock(sf::Vector2f a_pos);
};

class GreyBlock : Block // 50 score
{
    GreyBlock(float a_x , float a_y);
    GreyBlock(sf::Vector2f a_pos);
};

class RedwBlock : Block // 90
{
    RedwBlock(float a_x , float a_y);
    RedwBlock(sf::Vector2f a_pos);
};


class YellowBlock : Block // indestructible
{
    YellowBlock(float a_x , float a_y);
    YellowBlock(sf::Vector2f a_pos);
};

}//namespace arkanoid
#endif //BLOCK_H