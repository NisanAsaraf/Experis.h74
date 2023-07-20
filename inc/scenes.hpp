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
};

class Title_Screen : public Scene
{
public:
    Title_Screen();
    void create() override;
    
private:
    std::unique_ptr<Button> m_start_game;
    std::unique_ptr<Button> m_quit_game;
    Font m_font;
    Text m_title_screen_text;
};

class Level_One //: public Scene
{
public:
    Level_One();
    void create();
    std::vector<std::unique_ptr<Block>>& get_blocks();
    void reset();

private:
    std::vector<std::unique_ptr<Block>> blocks;
};

}
#endif //SCENE_H