#include "../inc/UI.hpp"

namespace arkanoid
{
using namespace sf;

Button::Button(Vector2f a_pos, std::string const& a_text, Font& a_font)
{
    m_button = std::make_unique<RectangleShape>(Vector2f(100.0f,40.0f));
    m_button->setFillColor(Color::White);

    m_button_text.setFont(a_font);
    m_button_text.setString(a_text);
    m_button_text.setCharacterSize(20);
    m_button_text.setFillColor(Color::Black);

    m_button_text.setPosition(a_pos.x + 10, a_pos.y + 10);

}

FloatRect Button::getBounds()
{
    return m_button->getGlobalBounds();
}

void Button::setPosition(Vector2f new_pos)
{
    m_button->setPosition(new_pos);
}

void Button::setText(std::string const& new_str)
{
    m_button_text.setString(new_str);
}

}//namespace arkanoid
