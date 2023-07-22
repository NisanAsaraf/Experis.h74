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

void Illustrator::draw_win_screen(Font& a_font, RenderWindow& a_window)
{
    Text text;
    Clock clk;
    Event event;
    bool quit = false;
    
    text.setFont(a_font);
    text.setString("YOU WIN!");
    text.setCharacterSize(100);
    text.setFillColor(Color::Green);
    text.setPosition(SCREEN_WIDTH/4 + 40, SCREEN_HEIGHT/3);

    while(clk.getElapsedTime().asSeconds() < 10)
    {
        a_window.draw(text);
        a_window.display();
        while (a_window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                quit = true;
                break;
            }
        }
        if(quit)
        {
            break;
        }
    }
}

void Illustrator::draw_game_over_screen(Font& a_font, RenderWindow& a_window)
{
    Text text;
    Clock clk;
    Event event;
    bool quit = false;

    text.setFont(a_font);
    text.setString("GAME OVER!");
    text.setCharacterSize(100);
    text.setFillColor(Color::Red);
    text.setPosition(SCREEN_WIDTH/4 - 20, SCREEN_HEIGHT/3 );

    while(clk.getElapsedTime().asSeconds() < 20)
    {
        a_window.draw(text);
        a_window.display();
        while (a_window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                a_window.close();
                quit = true;
            }
        }
        if(quit)
        {
            break;
        }          
    }
}

}//namespace arkanoid
