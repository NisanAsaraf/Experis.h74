#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "life.hpp"
#include "UI.hpp"
#include "abs_scene.hpp"
#include "leaderboard.hpp"
#include <vector>

namespace arkanoid
{

enum class GameState
{
    TitleScreen,
    Level,
    ScoreBoard,
    Paused,
};

class Title_Screen : public Scene
{
public:
    Title_Screen();
    void create() override;
    void reset() override;
    size_t get_win_score() const override;
    size_t get_level_number() const override;
};


class Level_One : public Scene
{
public:
    Level_One();
    void create() override;
    void reset() override;
    size_t get_win_score() const override;
    size_t get_level_number() const override;
private:
    void make_blocks(); 
};

class Level_Two : public Scene
{
public:
    Level_Two();
    void create() override;
    void reset() override;
    size_t get_win_score() const override;
    size_t get_level_number() const override;
private:
    void make_blocks(); 
};

class Level_Three : public Scene
{
public:
    Level_Three();
    void create() override;
    void reset() override;
    size_t get_win_score() const override;
    size_t get_level_number() const override;
private:
    void make_blocks(); 
};


class Score_Board : public Scene
{
public:
    Score_Board(std::vector<PlayerData>&);
    void create() override;
    void reset() override;

    std::vector<sf::Text> const& getTexts();
    sf::Text& getHeader();

    size_t get_win_score() const;
    size_t get_level_number() const;
private:
    std::vector<PlayerData> m_players;
    sf::Text m_header;
    std::vector<sf::Text> m_texts;
};

}
#endif //SCENE_H