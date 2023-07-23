#ifndef LIFE_H
#define LIFE_H
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <random>

namespace arkanoid
{

class Life
{
    
public:
    Life(sf::Vector2f);
    std::unique_ptr<sf::Sprite> const& get();
private:
    std::unique_ptr<sf::Texture> heartTexture;
    std::unique_ptr<sf::Sprite> heartSprite;
};

}//namespace arkanoid

#endif