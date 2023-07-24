#include "scenes.hpp"
#include <memory>

namespace arkanoid
{
using namespace sf;

Title_Screen::Title_Screen()
{
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("/home/nisan/Experis.h74/assets/textures/BG/titleBG.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Title_Screen::create()
{
    Texture startButton, quitButton;
    startButton.loadFromFile("/home/nisan/Experis.h74/assets/textures/Buttons/start_button.png");
    quitButton.loadFromFile("/home/nisan/Experis.h74/assets/textures/Buttons/quit_button.png");

    std::unique_ptr<Button> m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.3, SCREEN_HEIGHT/1.9), startButton);
    std::unique_ptr<Button> m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.13, SCREEN_HEIGHT/1.5), quitButton);

    buttons.emplace_back(std::move(m_start_game));
    buttons.emplace_back(std::move(m_quit_game));
}

std::vector<std::unique_ptr<Button>>& Title_Screen::get_vector()
{
    return buttons;
}

void Title_Screen::reset()
{
    create();
}

std::unique_ptr<Texture> const& Title_Screen::get_BG()
{
    return backgroundTexture;
}

Level_One::Level_One()
{

}

void Level_One::create()
{
    make_player();
    make_blocks();
    make_border(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_kill_zone(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    make_paddle();
    spawn_ball();
}

void Level_One::make_player()
{
    m_player = std::make_unique<Player>();
}

void Level_One::make_blocks()
{
    size_t row, col;

    row = 3;
    col = 5;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("/home/nisan/Experis.h74/assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }

    const int blockWidth = 100;
    const int blockHeight = 40;
    
    const int spacingX = 1;
    const int spacingY = 1;

    blocks.reserve(row * col);
    
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            int x = 150 + spacingX + j * (blockWidth + spacingX);
            int y = 100 + spacingY + i * (blockHeight + spacingY);
            std::unique_ptr<Block> block = std::make_unique<WhiteBlock>( x, y);
            blocks.emplace_back(std::move(block)); 
        }
    }
}

void Level_One::make_paddle()
{
    paddle = std::make_unique<Paddle>();
}

void Level_One::make_kill_zone(Vector2f a_size)
{
    kill_zone = std::make_unique<RectangleShape>(a_size);
    kill_zone->setPosition(0, a_size.y - 10);
    kill_zone->setFillColor(Color::Transparent);
}

void Level_One::make_border(Vector2f a_size)
{
    Color Teal(0, 128, 128);
    border = std::make_unique<sf::RectangleShape>(a_size - Vector2f(10.0f,10.0f));

    border->setFillColor(Color::Transparent);
    border->setPosition(5.0f, 5.0f);
    border->setOutlineThickness(5.0f);
    border->setOutlineColor(Teal);
}

void Level_One::spawn_ball()
{
    balls.emplace_back(std::make_unique<Ball>());
}

void Level_One::paddle_reset()
{
    paddle->reset();
}

void Level_One::reset()
{
    blocks.clear();
    paddle_reset();
    balls.clear();
    m_player->reset();
}

std::vector<std::unique_ptr<Block>>& Level_One::get_vector()
{
    return blocks;
}

std::unique_ptr<Texture> const& Level_One::get_BG()
{
    return backgroundTexture;
}

Paddle& Level_One::get_paddle()
{
    return *paddle;
}

std::unique_ptr<RectangleShape> const& Level_One::get_kill_zone()
{
    return kill_zone;
}

std::unique_ptr<RectangleShape> const& Level_One::get_border()
{
    return border;
}

std::vector<std::unique_ptr<Ball>> const& Level_One::get_balls()
{
    return balls;
}

Score_Board::Score_Board(std::vector<PlayerData>& a_players)
{
    m_players = a_players;
    backgroundTexture = std::make_unique<Texture>();
    m_header = std::make_unique<Text>();

    m_font = std::make_unique<Font>();
    if(!backgroundTexture->loadFromFile("/home/nisan/Experis.h74/assets/textures/BG/ScoreBoard_BG.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    if(!m_font->loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

std::vector<Text> const& Score_Board::getTexts()
{
    return m_texts;
}

std::unique_ptr<Texture> const& Score_Board::getBG()
{
    return backgroundTexture;
}

std::unique_ptr<Text> const& Score_Board::getHeader()
{
    return m_header;
}

void Score_Board::reset()
{

}

void Score_Board::create()
{
    m_header->setFont(*m_font);
    m_header->setCharacterSize(60);
    m_header->setFillColor(Color::White);
    m_header->setPosition(SCREEN_WIDTH/3, 10);
    m_header->setString("LEADERBOARD");

    for(size_t i = m_players.size(); i > 0; i--)
    {
        Text text;
        text.setFont(*m_font);
        text.setCharacterSize(30);
        text.setFillColor(Color::White);
        text.setPosition(SCREEN_WIDTH / 2 - 50, 100 + 40*i);
        text.setString(std::string(m_players.at(i - 1).name) + "    " + std::to_string(m_players.at(i - 1).score));
        m_texts.push_back(text);
    }
}

} // namespace arkanoid