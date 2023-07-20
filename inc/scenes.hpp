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

class Level_One //: Level
{
public:

    Level_One(size_t row, size_t col);

    std::vector<std::unique_ptr<Block>>& get_blocks();
    void reset();

    ~Level_One() = default;

private:
    std::vector<std::unique_ptr<Block>> blocks;
};

}
#endif //SCENE_H