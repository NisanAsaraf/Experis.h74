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
    Button(Vector2f, std::string const&, Font&);
    FloatRect getBounds();
    Text const& getText();
    void setPosition(Vector2f);
    void setText(std::string const&);
    void setButtonColor(Color);
    const RectangleShape& getShape() const;
private:
    std::unique_ptr<RectangleShape> m_button;
    Text m_button_text;
};

}//namespace arkanoid
#endif