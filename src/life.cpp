#include "life.hpp"
namespace arkanoid
{
using namespace sf;

Life::Life(Vector2f a_pos)
{
    heartTexture = std::make_unique<Texture>();
    if (!(*heartTexture).loadFromFile("/home/nisan/Experis.h74/assets/textures/Heart/heart.png")) 
    {
        throw std::runtime_error("Failed to load font from file.");
    }

    heartSprite = std::make_unique<Sprite>();
    heartSprite->setPosition(a_pos);
    heartSprite->setScale(0.2f, 0.2f);
    heartSprite->setTexture(*heartTexture);
}

std::unique_ptr<Sprite> const& Life::get()
{
    return heartSprite;
}

} // namespace arkanoid

