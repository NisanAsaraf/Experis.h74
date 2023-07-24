#ifndef ABS_BLOCK_H
#define ABS_BLOCK_H
#include <SFML/Graphics.hpp>

namespace arkanoid
{
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

}//arkanoid


#endif