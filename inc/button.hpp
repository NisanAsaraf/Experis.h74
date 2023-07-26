#ifndef BUTTON_H
#define BUTTON_H
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

class RandomNumberGenerator
{
public:
    static int getRandomNumber()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 4);
        return dis(gen);
    } 
};


class Button
{
public:
    Button(sf::Vector2f a_pos, sf::Texture const& a_texture, sf::Texture const& a_hoverTexture);
    sf::FloatRect getBounds();
    sf::Text const& getText();
    void setPosition(sf::Vector2f a_v);
    void setText(std::string const& a_str);
    void setButtonColor(sf::Color a_color);
    const sf::Sprite& getShape() const;
    void on_normal();
    void on_hover();
    void on_click();
private:
    std::unique_ptr<sf::Sprite> m_buttonSprite;
    std::unique_ptr<sf::Texture> m_buttonTexture;
    std::unique_ptr<sf::Texture> m_button_hover_Texture;
    std::unique_ptr<sf::Texture> m_button_click_Texture;
};

}//namespace arkanoid
#endif