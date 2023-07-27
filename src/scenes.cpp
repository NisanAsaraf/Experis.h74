#include "scenes.hpp"
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
    Texture startButton, quitButton, startButtonHover, quitButtonHover; 
    startButton.loadFromFile("../../assets/textures/Buttons/start_button.png");
    startButtonHover.loadFromFile("../../assets/textures/Buttons/start_button_hover.png");
    
    quitButton.loadFromFile("../../assets/textures/Buttons/quit_button.png");
    quitButtonHover.loadFromFile("../../assets/textures/Buttons/quit_button_hover.png");

    std::unique_ptr<Button> m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 25), startButton, startButtonHover);
    std::unique_ptr<Button> m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 125), quitButton, quitButtonHover);
    
    buttons.emplace_back(std::move(m_start_game));
    buttons.emplace_back(std::move(m_quit_game));

    lvl = 0;
}

void Title_Screen::reset()
{
    create();
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
    backgroundTexture = std::make_unique<Texture>();
    lvl = 1;
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
    lvl = 2;
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
    lvl = 3;
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

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- */ 

Level_Four::Level_Four()
{

}

void Level_Four::create()
{
    make_blocks();
    make_border(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_kill_zone(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_paddle();
    spawn_ball();
    lvl = 4;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("../../assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Level_Four::make_blocks()
{
    std::ifstream file("../../assets/levels/level-4.dat");
    if (!file)
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    load_blocks_from_json(file);
}

void Level_Four::reset()
{
    blocks.clear();
    paddle_reset();
    balls.clear();
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
    lvl = 0;
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

} // namespace arkanoid