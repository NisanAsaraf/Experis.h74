#include "../inc/animations.hpp"

namespace arkanoid
{
    
void Illustrator::draw_BG_title(Title_Screen& a_titlescreen,RenderWindow& a_window)
{
    Sprite backgroundSprite;
    a_window.clear();

    backgroundSprite.setTexture(*(a_titlescreen.get_BG()));     
    backgroundSprite.setScale(0.2f, 0.2f);
    a_window.draw(backgroundSprite);
}

void Illustrator::draw_BG_level(Level_One& a_level_one,RenderWindow& a_window)
{
    Sprite backgroundSprite;
    a_window.clear();

    backgroundSprite.setTexture(*a_level_one.get_BG());     
    backgroundSprite.setScale(0.2f, 0.2f);
    a_window.draw(backgroundSprite);
}

void Illustrator::draw_BG_scoreboard(Score_Board& a_scoreBoard,RenderWindow& a_window)
{
    Texture* backgroundTexture = a_scoreBoard.getBG().get();
    Sprite backgroundSprite;
    backgroundSprite.setTexture(*backgroundTexture);     
    a_window.clear();
    backgroundSprite.setScale(0.2f, 0.25f);
    a_window.draw(backgroundSprite);

}

void Illustrator::draw_title_screen(Title_Screen& a_titlescreen,RenderWindow& a_window)
{
    auto const& buttons = a_titlescreen.get_vector();
    a_window.draw(a_titlescreen.getTitleText());

    for (auto& buttonPtr : buttons)
    {
        Button& button = *buttonPtr;
        draw_shape(button, a_window);
        a_window.draw(button.getText());
    }
}

void Illustrator::draw_level_one(Level_One& a_level_one,RenderWindow& a_window)
{
    auto const& blocks = a_level_one.get_vector();
    for (auto& blockPtr : blocks)
    { 
        Block& block = *blockPtr;
        draw_shape(block, a_window);
    }
}

void Illustrator::draw_scoreboard(Score_Board& a_scoreBoard,RenderWindow& a_window)
{
    std::vector<Text> texts = a_scoreBoard.getTexts();
    a_window.draw(*a_scoreBoard.getHeader());
    for(auto& text: texts)
    {   
        a_window.draw(text);
    }
}
}//namespace arkanoid
