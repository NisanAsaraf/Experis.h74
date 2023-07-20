#include "../inc/UI.hpp"

namespace arkanoid
{
using namespace sf;

Button::Button(Vector2f a_pos , std::string const& m_text)
{
    m_button = std::make_unique<RectangleShape>(a_pos);
    m_button_text.setString(m_text);
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

class Title_Screen : public Scene
{
public:
    void Create() const override;
    

};

}//namespace arkanoid
