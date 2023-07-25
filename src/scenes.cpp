#include "scenes.hpp"
#include <memory>
#include "UI.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <nlohmann/json.hpp>

namespace arkanoid
{
using namespace sf;


Title_Screen::Title_Screen()
{
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("../../assets/textures/BG/titleBG.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Title_Screen::create()
{
    Texture startButton, quitButton;
    startButton.loadFromFile("../../assets/textures/Buttons/start_button.png");
    quitButton.loadFromFile("../../assets/textures/Buttons/quit_button.png");

    std::unique_ptr<Button> m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.3, SCREEN_HEIGHT/1.9), startButton);
    std::unique_ptr<Button> m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.13, SCREEN_HEIGHT/1.5), quitButton);
    
    buttons.emplace_back(std::move(m_start_game));
    buttons.emplace_back(std::move(m_quit_game));


}

void Title_Screen::reset()
{
    create();
}

size_t Title_Screen::get_win_score() const
{
    return 0;
}

size_t Title_Screen::get_level_number() const
{
    return 0;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------- */

Level_One::Level_One()
{

}

void Level_One::create()
{
    make_blocks();
    make_border(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_kill_zone(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_paddle();
    spawn_ball();
    win_score = LEVEL_ONE_SCORE;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("../../assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Level_One::make_blocks()
{
    std::ifstream file("../../assets/levels/level-1.dat");
    if (!file)
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    load_blocks_from_json(file);
}

void Level_One::reset()
{
    blocks.clear();
    paddle_reset();
    balls.clear();
}

size_t Level_One::get_win_score() const
{
    return win_score;
}

size_t Level_One::get_level_number() const
{
    return 1;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------- */

Level_Two::Level_Two()
{

}

void Level_Two::create()
{
    make_blocks();
    make_border(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_kill_zone(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_paddle();
    spawn_ball();
    win_score = LEVEL_TWO_SCORE;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("../../assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Level_Two::make_blocks()
{
    std::ifstream file("../../assets/levels/level-2.dat");
    if (!file)
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    load_blocks_from_json(file);
}

void Level_Two::reset()
{
    blocks.clear();
    paddle_reset();
    balls.clear();
}


size_t Level_Two::get_win_score() const
{
    return win_score;
}

size_t Level_Two::get_level_number() const
{
    return 2;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------- */

Level_Three::Level_Three()
{

}

void Level_Three::create()
{
    make_blocks();
    make_border(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_kill_zone(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_paddle();
    spawn_ball();
    win_score = LEVEL_THREE_SCORE;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("../../assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Level_Three::make_blocks()
{
    std::ifstream file("../../assets/levels/level-3.dat");
    if (!file)
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    load_blocks_from_json(file);
}

void Level_Three::reset()
{
    blocks.clear();
    paddle_reset();
    balls.clear();
}


size_t Level_Three::get_win_score() const
{
    return win_score;
}

size_t Level_Three::get_level_number() const
{
    return 3;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- */ 

Score_Board::Score_Board(std::vector<PlayerData>& a_players)
{
    m_players = a_players;
    backgroundTexture = std::make_unique<Texture>();

    if(!backgroundTexture->loadFromFile("../../assets/textures/BG/ScoreBoard_BG.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Score_Board::reset()
{

}

void Score_Board::create()
{
    m_header.setCharacterSize(60);
    m_header.setFillColor(Color::White);
    m_header.setPosition(SCREEN_WIDTH/3, 10);
    m_header.setString("LEADERBOARD");

    for(size_t i = m_players.size(); i > 0; i--)
    {
        Text text;
        text.setCharacterSize(30);
        text.setFillColor(Color::White);
        text.setPosition(SCREEN_WIDTH / 2 - 50, 100 + 40*i);
        text.setString(std::string(m_players.at(i - 1).name) + "    " + std::to_string(m_players.at(i - 1).score));
        m_texts.push_back(text);
    }
}

size_t Score_Board::get_win_score() const
{
    return 0;
}

size_t Score_Board::get_level_number() const
{
    return 42;
}

} // namespace arkanoid