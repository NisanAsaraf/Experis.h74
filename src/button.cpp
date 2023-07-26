#include "button.hpp"

namespace arkanoid
{
using namespace sf;

Button::Button(Vector2f a_pos, Texture const& a_texture, Texture const& a_hoverTexture)
{
    m_buttonTexture = std::make_unique<Texture>(); 
    m_button_hover_Texture = std::make_unique<Texture>();
    
    (*m_buttonTexture) = a_texture;
    (*m_button_hover_Texture) = a_hoverTexture;

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

void Button::on_normal()
{
    m_buttonSprite->setTexture(*m_buttonTexture);
}

void Button::on_hover()
{
    m_buttonSprite->setTexture(*m_button_hover_Texture);
}

}//namespace arkanoid
