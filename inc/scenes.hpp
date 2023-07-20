#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "UI.hpp"
#include <vector>

namespace arkanoid
{

class Scene
{
public:
    virtual void create() = 0;
    virtual void reset() = 0;
};

class Title_Screen : public Scene
{
public:
    Title_Screen();
    void create() override;
    void reset() override;
    Text const& getTitleText();
    std::vector<std::unique_ptr<Button>>& get_vector();

private:
    std::vector<std::unique_ptr<Button>> buttons;
    Font m_font;
    Text m_title_screen_text;
};

class Level_One : public Scene
{
public:
    Level_One();
    void create() override;
    void reset() override;
    std::vector<std::unique_ptr<Block>>& get_vector();
    
private:
    std::vector<std::unique_ptr<Block>> blocks;
};

}
#endif //SCENE_H