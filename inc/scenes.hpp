#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "UI.hpp"
#include "life.hpp"
#include "leaderboard.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include <vector>

namespace arkanoid
{

enum class GameState
{
    TitleScreen,
    Level1,
    ScoreBoard,
    Paused,
};

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
    std::vector<std::unique_ptr<Button>>& get_vector();
    std::unique_ptr<sf::Texture> const& get_BG();

private:
    std::vector<std::unique_ptr<Button>> buttons;
    std::unique_ptr<sf::Texture> backgroundTexture;
};


class Level_One : public Scene
{
public:
    Level_One();
    void create() override;
    void reset() override;

    std::vector<std::unique_ptr<Block>>& get_vector();
    std::unique_ptr<sf::Texture> const& get_BG();
    Paddle& get_paddle();
    std::unique_ptr<sf::RectangleShape> const& get_kill_zone();
    std::unique_ptr<sf::RectangleShape> const& get_border();
    std::vector<std::unique_ptr<Ball>> const& get_balls();
private:
    void make_blocks(); 
    void make_player();
    void make_paddle();
    void make_kill_zone(sf::Vector2f a_size);
    void make_border(sf::Vector2f a_size);
    void spawn_ball();
    void paddle_reset();
    
private:
    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::RectangleShape> border;
    std::unique_ptr<sf::RectangleShape> kill_zone;
    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Paddle> paddle;
};


class Score_Board : public Scene
{
public:
    Score_Board(std::vector<PlayerData>&);
    void create() override;
    void reset() override;
    std::vector<sf::Text> const& getTexts();
    std::unique_ptr<sf::Texture> const& getBG();
    std::unique_ptr<sf::Text> const& getHeader();

private:
    std::vector<PlayerData> m_players;
    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Font> m_font;
    std::unique_ptr<sf::Text> m_header;
    std::vector<sf::Text> m_texts;
};

}
#endif //SCENE_H