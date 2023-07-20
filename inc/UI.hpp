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
    void setPosition(Vector2f);
    void setText(std::string const&);
    void setButtonColor(Color);
private:
    std::unique_ptr<RectangleShape> m_button;
    Text m_button_text;
};

class Scene
{
public:
    virtual void Create() = 0;
    virtual ~Scene() = default;
};

class Title_Screen : public Scene
{
public:
    Title_Screen();
    void Create() override;
    
private:
    std::unique_ptr<Button> m_start_game;
    std::unique_ptr<Button> m_quit_game;
    Font m_font;
    Text m_title_screen_text;
};

}//namespace arkanoid
#endif