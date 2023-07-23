#include "../inc/animations.hpp"

namespace arkanoid
{

Illustrator::Illustrator()
{
    if(!m_font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
    {
        throw std::runtime_error("Error load font");
    }
}

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
    Texture msg_texture;
    Sprite msg_sprite;
    msg_texture.loadFromFile("/home/nisan/Experis.h74/assets/textures/Messages/arkanoid_color.png");
    msg_sprite.setTexture(msg_texture);
    msg_sprite.setColor(Color::White);
    msg_sprite.setScale(0.4f,0.4f);
    msg_sprite.setPosition(SCREEN_WIDTH/12 - 10, SCREEN_HEIGHT/7);

    a_window.draw(msg_sprite);

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
    a_window.draw(*a_level_one.get_border());
    a_window.draw(*a_level_one.get_kill_zone());
    draw_shape(*(a_level_one.get_paddle()),a_window);

    auto const& balls = a_level_one.get_balls();
    for (auto& ballPtr : balls)
    { 
        Ball& ball = *ballPtr;
        draw_shape(ball, a_window);
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

void Illustrator::draw_win_screen(RenderWindow& a_window)
{
    Texture msg_texture;
    Sprite msg_sprite;
    msg_texture.loadFromFile("/home/nisan/Experis.h74/assets/textures/Messages/you_win.png");
    msg_sprite.setTexture(msg_texture);
    msg_sprite.setScale(0.5f,0.5f);
    msg_sprite.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3);
    Clock clk;
    Event event;
    bool quit = false;

    while(clk.getElapsedTime().asSeconds() < 10)
    {
        a_window.draw(msg_sprite);
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

void Illustrator::draw_game_over_screen(RenderWindow& a_window)
{
    Texture msg_texture;
    Sprite msg_sprite;
    msg_texture.loadFromFile("/home/nisan/Experis.h74/assets/textures/Messages/game_over.png");
    msg_sprite.setTexture(msg_texture);
    msg_sprite.setScale(0.8f,0.8f);
    msg_sprite.setPosition(SCREEN_WIDTH/4, SCREEN_HEIGHT/3);

    Clock clk;
    Event event;
    bool quit = false;

    while(clk.getElapsedTime().asSeconds() < 20)
    {
        a_window.draw(msg_sprite);
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

void Illustrator::draw_score(size_t a_score ,RenderWindow& a_window)
{
    Text scoreText;
    scoreText.setFont(m_font);
    scoreText.setString("Score: " + std::to_string(a_score));

    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(30, 30);
    a_window.draw(scoreText);
}

void Illustrator::draw_pause(RenderWindow& a_window)
{
    Text text;
    text.setFont(m_font);
    text.setString("PAUSED");

    text.setCharacterSize(100);
    text.setFillColor(Color::White);
    text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3);
    a_window.draw(text);
}

void Animator::animate_ball(Ball& a_ball)
{
    a_ball.move(a_ball.getVelocity());
}

void Animator::animate_paddle_right(Paddle& a_paddle , Clock& a_clock)
{
    a_paddle.right(a_clock);
    a_paddle.move(a_paddle.getVelocity());
}

void Animator::animate_paddle_left(Paddle& a_paddle, Clock& a_clock)
{
    a_paddle.left(a_clock);
    a_paddle.move(a_paddle.getVelocity());
}

void Animator::animate_paddle_stop(Paddle& a_paddle)
{
    a_paddle.stop();
    a_paddle.move(a_paddle.getVelocity());
}

}//namespace arkanoid
