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

Title_Screen::Title_Screen()
{
    if (!m_font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Title_Screen::Create()
{
    m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), "Start Game");
    m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/4), "Quit Game");

    m_title_screen_text.setFont(m_font);
    m_title_screen_text.setString("Arkanoid - Nisan");
    m_title_screen_text.setCharacterSize(100);
    m_title_screen_text.setFillColor(Color::White);
    m_title_screen_text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3); 
}

}//namespace arkanoid
