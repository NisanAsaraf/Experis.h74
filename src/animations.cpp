#include "../inc/animations.hpp"

namespace arkanoid
{

void Illustrator::draw_BG_scoreboard(Score_Board& a_scoreBoard,RenderWindow& a_window)
{
    Texture* backgroundTexture = a_scoreBoard.getBG().get();
    Sprite backgroundSprite;
    backgroundSprite.setTexture(*backgroundTexture);     
    a_window.clear();
    backgroundSprite.setScale(0.2f, 0.25f);
    a_window.draw(backgroundSprite);

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
