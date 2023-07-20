#include "../inc/scenes.hpp"
#include <memory>

namespace arkanoid
{

Title_Screen::Title_Screen()
{
    if (!m_font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}

void Title_Screen::Create()
{
    m_start_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), "Start Game", m_font);
    m_quit_game = std::make_unique<Button>(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/4), "Quit Game" , m_font);

    m_title_screen_text.setFont(m_font);
    m_title_screen_text.setString("Arkanoid - Nisan");
    m_title_screen_text.setCharacterSize(100);
    m_title_screen_text.setFillColor(Color::White);
    m_title_screen_text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3); 
}

Level_One::Level_One(size_t row, size_t col)
{
    std::vector<sf::Color> block_colors;

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

std::vector<std::unique_ptr<Block>>& Level_One::get_blocks()
{
    return blocks;
}

} // namespace arkanoid
