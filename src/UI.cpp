#include "UI.hpp"

namespace arkanoid
{
using namespace sf;

Button::Button(Vector2f a_pos, Texture const& a_texture)
{
    m_buttonTexture = std::make_unique<Texture>(); 
    (*m_buttonTexture) = a_texture;

    m_buttonSprite = std::make_unique<Sprite>(*m_buttonTexture);
    m_buttonSprite->setPosition(a_pos - Vector2f(20.0f, 10.0f));
    m_buttonSprite->setColor(Color::White);
    m_buttonSprite->setScale(0.5f,0.5f);
}

FloatRect Button::getBounds()
{
    return m_buttonSprite->getGlobalBounds();
}

const Sprite& Button::getShape() const
{
    return *m_buttonSprite;
}

void Button::setPosition(Vector2f new_pos)
{
    m_buttonSprite->setPosition(new_pos);
}

void Button::setText(std::string const& new_str)
{
    m_button_text.setString(new_str);
}

Text const& Button::getText()
{
    return m_button_text;
}

void Button::on_hover()
{
}

}//namespace arkanoid
