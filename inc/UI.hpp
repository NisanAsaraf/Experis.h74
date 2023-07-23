#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <random>

namespace arkanoid
{
using namespace sf;

class RandomColorGenerator
{
public:
    static Color getRandomColor()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return Color(dis(gen), dis(gen), dis(gen));
    } 
};

class Button
{
public:
    Button(Vector2f, Texture const&);
    FloatRect getBounds();
    Text const& getText();
    void setPosition(Vector2f);
    void setText(std::string const&);
    void setButtonColor(Color);
    const Sprite& getShape() const;
private:
    std::unique_ptr<Sprite> m_buttonSprite;
    std::unique_ptr<Texture> m_buttonTexture;
    Text m_button_text;

};

}//namespace arkanoid
#endif
