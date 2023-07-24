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
    int getScoreValue(size_t a_lvl = 1) const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getSize() const ;
    const sf::RectangleShape& getShape() const;
    bool isVanished() const ;
    virtual void Collision() = 0;
    
protected:
    void vanish();
    std::unique_ptr<sf::RectangleShape> shape;
    std::unique_ptr<sf::Texture> blockTexture;
    int score;
    bool vanished;
};

class WhiteBlock : public Block // 50 score
{
public:
    WhiteBlock(float a_x , float a_y);
    WhiteBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class TealBlock : Block // 70 score
{
    TealBlock(float a_x , float a_y);
    TealBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class BrownBlock : Block // 60 score
{
    BrownBlock(float a_x , float a_y);
    BrownBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class OrangeBlock : Block // 120 score
{
    OrangeBlock(float a_x , float a_y);
    OrangeBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class GreenBlock : Block // 80 score
{
    GreenBlock(float a_x , float a_y);
    GreenBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class PurpleBlock : Block // 110 score
{
    PurpleBlock(float a_x , float a_y);
    PurpleBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class BlueBlock : Block // 100 score
{
    BlueBlock(float a_x , float a_y);
    BlueBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class GrayBlock : Block // 50 score
{
    GrayBlock(float a_x , float a_y);
    GrayBlock(sf::Vector2f a_pos);
    void Collision() override;
};

class RedBlock : Block // 90
{
    RedBlock(float a_x , float a_y);
    RedBlock(sf::Vector2f a_pos);
    void Collision() override;
};


class YellowBlock : Block // indestructible
{
    YellowBlock(float a_x , float a_y);
    YellowBlock(sf::Vector2f a_pos);
    void Collision() override;
};

}//namespace arkanoid
#endif //BLOCK_H