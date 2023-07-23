#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <random>

namespace arkanoid
{

class RandomColorGenerator
{
public:
    static sf::Color getRandomColor()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return sf::Color(dis(gen), dis(gen), dis(gen));
    } 
};

class Button
{
public:
    Button(sf::Vector2f, sf::Texture const&);
    sf::FloatRect getBounds();
    sf::Text const& getText();
    void setPosition(sf::Vector2f);
    void setText(std::string const&);
    void setButtonColor(sf::Color);
    const sf::Sprite& getShape() const;
private:
    std::unique_ptr<sf::Sprite> m_buttonSprite;
    std::unique_ptr<sf::Texture> m_buttonTexture;
    sf::Text m_button_text;

};

}//namespace arkanoid
#endif
