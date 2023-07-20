#include "../inc/UI.hpp"

namespace arkanoid
{
using namespace sf;

Button::Button(Vector2f a_pos, std::string const& a_text, Font& a_font)
{
    m_button = std::make_unique<RectangleShape>(Vector2f(100.0f,40.0f));
    m_button->setFillColor(Color::White);
    m_button->setPosition(a_pos - Vector2f(10.0f,10.0f));

    m_button_text.setFont(a_font);
    m_button_text.setString(a_text);
    m_button_text.setCharacterSize(20);
    m_button_text.setFillColor(Color::Black);

    m_button_text.setPosition(a_pos);

}

FloatRect Button::getBounds()
{
    return m_button->getGlobalBounds();
}

const RectangleShape& Button::getShape() const
{
    return *m_button;
}

void Button::setPosition(Vector2f new_pos)
{
    m_button->setPosition(new_pos);
}

void Button::setText(std::string const& new_str)
{
    m_button_text.setString(new_str);
}

Text const& Button::getText()
{
    return m_button_text;
}

}//namespace arkanoid
