#include "../inc/scenes.hpp"
#include <memory>

namespace arkanoid
{

Title_Screen::Title_Screen()
{
    if (!m_font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
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

    m_title_screen_text.setFont(m_font);
    m_title_screen_text.setString("Arkanoid - Nisan");
    m_title_screen_text.setCharacterSize(100);
    m_title_screen_text.setFillColor(Color::White);
    m_title_screen_text.setPosition(SCREEN_WIDTH/8, SCREEN_HEIGHT/4);

    buttons.emplace_back(std::move(m_start_game));
    buttons.emplace_back(std::move(m_quit_game));
}

Text const& Title_Screen::getTitleText()
{
    return m_title_screen_text;
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
    size_t row, col;

    row = 3;
    col = 5;
    Texture b1,b2,b3;
    backgroundTexture = std::make_unique<Texture>();

    if (!(*backgroundTexture).loadFromFile("/home/nisan/Experis.h74/assets/textures/BG/neon.jpg"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }

    if (!b1.loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/01-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    if (!b2.loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/03-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    if (!b3.loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/05-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }

    std::vector<Texture> textures;
    textures.push_back(b1);
    textures.push_back(b2);
    textures.push_back(b3);

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
            std::unique_ptr<Block> block = std::make_unique<Block>(textures.at(i), x, y);
            blocks.emplace_back(std::move(block)); 
        }
    }
}

void Level_One::reset()
{
    blocks.clear();
}

std::vector<std::unique_ptr<Block>>& Level_One::get_vector()
{
    return blocks;
}

std::unique_ptr<Texture> const& Level_One::get_BG()
{
    return backgroundTexture;
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