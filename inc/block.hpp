#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{

class Block
{
public:
    Block(sf::Texture a_texture, float a_x, float a_y);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getSize();
    bool isVanished();
    const sf::RectangleShape& getShape() const;
    void Collision() ;
private:
    void vanish();

private:
    std::unique_ptr<sf::RectangleShape> shape;
    std::unique_ptr<sf::Texture> blockTexture;
    bool vanished;

};

}//namespace arkanoid
#endif //BLOCK_H