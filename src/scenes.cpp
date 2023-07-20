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
}

void Title_Screen::create()
{
    std::unique_ptr<Button> m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.2, SCREEN_HEIGHT/2), "Start Game", m_font);
    std::unique_ptr<Button> m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2.2, SCREEN_HEIGHT/1.5), "Quit Game", m_font);

    m_title_screen_text.setFont(m_font);
    m_title_screen_text.setString("Arkanoid - Nisan");
    m_title_screen_text.setCharacterSize(100);
    m_title_screen_text.setFillColor(Color::Green);
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

Level_One::Level_One()
{
}

void Level_One::create()
{
    std::vector<sf::Color> block_colors;
    size_t row, col;

    row = 3;
    col = 5;

    block_colors.push_back(sf::Color::Green);
    block_colors.push_back(sf::Color::Magenta);
    block_colors.push_back(sf::Color::Cyan);

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
            Color brick_color = block_colors.at(i);

            std::unique_ptr<Block> block = std::make_unique<Block>(brick_color, x, y);
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

} // namespace arkanoid
