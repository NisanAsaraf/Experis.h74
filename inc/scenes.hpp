#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "UI.hpp"
#include "leaderboard.hpp"
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
    std::unique_ptr<Texture> const& get_BG();

private:
    std::vector<std::unique_ptr<Button>> buttons;
    Font m_font;
    Text m_title_screen_text;
    std::unique_ptr<Texture> backgroundTexture;
};

class Level_One : public Scene
{
public:
    Level_One();
    void create() override;
    void reset() override;
    std::vector<std::unique_ptr<Block>>& get_vector();
    std::unique_ptr<Texture> const& get_BG();
    
private:
    std::vector<std::unique_ptr<Block>> blocks;
    std::unique_ptr<Texture> backgroundTexture;
};

class Score_Board : public Scene
{
public:
    Score_Board(std::vector<PlayerData>&);
    void create() override;
    void reset() override;
    std::vector<Text> const& getTexts();
    std::unique_ptr<Texture> const& getBG();

private:
    std::vector<PlayerData> m_players;
    std::unique_ptr<Texture> backgroundTexture;
    std::unique_ptr<Font> m_font;
    std::vector<Text> m_texts;
};

}
#endif //SCENE_H