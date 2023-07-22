#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include "config.hpp"

namespace arkanoid
{
using namespace sf;

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

class Life
{
public:
    Life(Vector2f);
    std::unique_ptr<Sprite> const& get();
private:
    std::unique_ptr<Texture> heartTexture;
    std::unique_ptr<Sprite> heartSprite;
};

}//namespace arkanoid
#endif
