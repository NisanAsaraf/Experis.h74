#include "animations.hpp"

namespace arkanoid
{

using namespace sf;
Illustrator::Illustrator()
{
    if(!m_font.loadFromFile("../../assets/fonts/Antonio-Bold.ttf"))
    {
        throw std::runtime_error("Error load font");
    }
    if(!muteIcon.loadFromFile("../../assets/textures/Sound/sound_off.png"))
    {
        throw std::runtime_error("Error: load from file");
    }
    if(!soundIcon.loadFromFile("../../assets/textures/Sound/sound_on.png"))
    {
    throw std::runtime_error("Error: load from file");
    }

}

void Illustrator::draw_BG_title(Scene& a_titlescreen,RenderWindow& a_window)
{
    Sprite backgroundSprite;
    a_window.clear();

    backgroundSprite.setTexture(*(a_titlescreen.get_BG()));     
    backgroundSprite.setScale(0.2f, 0.2f);
    a_window.draw(backgroundSprite);
}

void Illustrator::draw_BG_level(Scene& a_level_one,RenderWindow& a_window)
{
    Sprite backgroundSprite;
    a_window.clear();

    backgroundSprite.setTexture(*a_level_one.get_BG());     
    backgroundSprite.setScale(0.2f, 0.2f);
    a_window.draw(backgroundSprite);
}

void Illustrator::draw_BG_scoreboard(Scene& a_scoreBoard,RenderWindow& a_window)
{
    Texture& backgroundTexture = *a_scoreBoard.get_BG();
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);     
    a_window.clear();
    backgroundSprite.setScale(0.2f, 0.25f);
    a_window.draw(backgroundSprite);

}

void Illustrator::draw_title_screen(Scene& a_titlescreen,RenderWindow& a_window)
{
    auto const& buttons = a_titlescreen.get_buttons();
    Texture msg_texture;
    Sprite msg_sprite;
    msg_texture.loadFromFile("../../assets/textures/Messages/arkanoid_color.png");
    msg_sprite.setTexture(msg_texture);
    msg_sprite.setColor(Color::White);
    msg_sprite.setScale(0.4f,0.4f);
    msg_sprite.setPosition(SCREEN_WIDTH/12 - 10, SCREEN_HEIGHT/7);

    a_window.draw(msg_sprite);

    for (auto& buttonPtr : buttons)
    {
        draw_button(*buttonPtr, a_window);
    }
}

void Illustrator::draw_level(Scene& a_level_one,RenderWindow& a_window)
{
    auto const& paddle = a_level_one.get_paddle();
    auto const& blocks = a_level_one.get_blocks();

    for (auto& blockPtr : blocks)
    { 
        Block& block = *blockPtr;
        draw_shape(block, a_window);
    }
    a_window.draw(*a_level_one.get_border());
    a_window.draw(*a_level_one.get_kill_zone());
    draw_shape(paddle,a_window);

    auto const& balls = a_level_one.get_balls();
    for (auto& ballPtr : balls)
    { 
        Ball& ball = *ballPtr;
        draw_shape(ball, a_window);
    }
}

void Illustrator::draw_scoreboard(Scene& a_scoreBoard,RenderWindow& a_window)
{
    auto& header = a_scoreBoard.getHeader();
    header.setFont(m_font);
    a_window.draw(a_scoreBoard.getHeader());

    std::vector<Text> texts = a_scoreBoard.getTexts();
    for(auto& text: texts)
    {   text.setFont(m_font);
        a_window.draw(text);
    }
}

void Illustrator::draw_life_bar(size_t lives,RenderWindow& a_window)
{
    for (size_t i = 1; i <= lives; i++)
    {
        Life life(Vector2f(30*i, 70));
        a_window.draw(*(life.get()));
    }
}

void Illustrator::draw_win_screen(RenderWindow& a_window)
{
    Texture msg_texture;
    Sprite msg_sprite;
    msg_texture.loadFromFile("../../assets/textures/Messages/you_win.png");
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
    msg_texture.loadFromFile("../../assets/textures/Messages/game_over.png");
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

void Illustrator::draw_button_hover(Button& a_button, sf::RenderWindow& a_window)
{
    a_button.on_hover();
    draw_shape(a_button, a_window);
}

void Illustrator::draw_button(Button& a_button, sf::RenderWindow& a_window)
{
    // a_button.on_normal();
    draw_shape(a_button, a_window);
}

void Illustrator::draw_mute_icon(sf::RenderWindow& window)
{
    Sprite muteSprite;
    muteSprite.setPosition(SCREEN_WIDTH - 150, 0);
    muteSprite.setTexture(muteIcon);
    window.draw(muteSprite);
}

void Illustrator::draw_sound_icon(sf::RenderWindow& window)
{
    Sprite soundSprite;
    soundSprite.setPosition(SCREEN_WIDTH - 150, 0);
    soundSprite.setTexture(soundIcon);
    window.draw(soundSprite);
}

bool Illustrator::draw_input_name_screen(std::string& a_string, RenderWindow& a_window)
{
    Text text("New high score!\n input name:", m_font, 50);
    text.setFillColor(Color::White);
    text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/4);
    Text inputText("", m_font, 30);
    std::string playerName;
    inputText.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3 + 100);
    inputText.setFillColor(Color::Cyan);

    bool quit = false;
    Event event;
    while(a_window.isOpen())
    {
        while (a_window.pollEvent(event)) 
        {
            if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                a_window.close();
                return false;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                quit = true;
                break;
            }
            else if (event.type == sf::Event::TextEntered) 
            {
                if (event.text.unicode < 128 && playerName.size() <= 16 && event.text.unicode != '\b') 
                {
                    playerName += static_cast<char>(event.text.unicode);
                    inputText.setString(playerName);
                } else if (event.text.unicode == '\b' && !playerName.empty()) 
                {
                    playerName.pop_back();
                    inputText.setString(playerName);
                }
            }
        }
        a_window.clear(Color::Black);
        a_window.draw(text);
        a_window.draw(inputText);
        a_window.display();

        if(quit)
        {
            break;
        }
    }
    a_string.assign(playerName);
    return true;
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
