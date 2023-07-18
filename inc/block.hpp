#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{

class Block
{
public:
    Block(sf::Color, float , float);

    sf::RectangleShape& operator*();

private:
    std::unique_ptr<sf::RectangleShape> block;

};

}//namespace arkanoid
#endif //BLOCK_H