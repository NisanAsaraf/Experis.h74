#ifndef MENUS_H
#define MENUS_H
#include <SFML/Graphics.hpp>

namespace arkanoid
{
using namespace sf;

class Button
{
public:
    FloatRect getBounds();
private:
    std::unique_ptr<RectangleShape> m_button;
    Text m_button_text;
};

class Menu
{
public:
    virtual void Create() const = 0;
    virtual ~Menu() = default;

};


class Title_Screen : public Menu
{
public:
    void Create() const override;
    
private:

};

}//namespace arkanoid
#endif