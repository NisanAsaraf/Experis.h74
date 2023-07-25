#include "window.hpp"

namespace arkanoid
{
using namespace sf;

Game_Window::Game_Window()
: window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
, "Arkanoid",Style::Titlebar | Style::Close)
{ 
    illustrator = std::make_unique<Illustrator>();
    animator = std::make_unique<Animator>();

    window.setFramerateLimit(64);
    window.setVerticalSyncEnabled(false);
}

void Game_Window::draw_background_title_screen(Scene& a_scene)
{
    illustrator->draw_BG_title(a_scene, window);
}

void Game_Window::draw_background_level_one(Scene& a_scene)
{
    illustrator->draw_BG_level(a_scene, window);
}

void Game_Window::Game_Window::draw_background_score_board(Scene& a_scene)
{
    illustrator->draw_BG_scoreboard(a_scene, window);
}

void Game_Window::draw_background(Scene& a_scene, GameState& currentGameState)
{
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            draw_background_title_screen(a_scene);
            break;

        case GameState::Level:
            draw_background_level_one(a_scene);
            break;

        case GameState::ScoreBoard:
            draw_background_score_board(a_scene);
            break;

        case GameState::Paused:
            break;
    }   
}

void Game_Window::draw_hearts(size_t lives)
{
    illustrator->draw_life_bar(lives, window);
}

void Game_Window::draw_score(size_t score)
{
    illustrator->draw_score(score , window);
}

void Game_Window::draw_pause_text()
{
    illustrator->draw_pause(window);
}

void Game_Window::draw_title_screen(Scene& a_scene)
{
    illustrator->draw_title_screen(a_scene, window);
}

void Game_Window::draw_level_one(Player& a_player, Scene& a_scene)
{
    illustrator->draw_level(a_scene, window);
    draw_hearts(a_player.get_lives());
}

void Game_Window::draw_scoreboard(Scene& a_scene)
{
    illustrator->draw_scoreboard(a_scene, window);
}

void Game_Window::draw_scene(Player& a_player,Scene& a_scene, GameState& currentGameState)
{  
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            draw_title_screen(a_scene);
            break;
        case GameState::Level:
            draw_level_one(a_player, a_scene);
            break;
        case GameState::ScoreBoard:
            draw_scoreboard(a_scene);
            break;
        case GameState::Paused:
            break;
    }
}

void Game_Window::run_title_screen(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    draw_background(a_scene, currentGameState);
    draw_scene(a_player, a_scene, currentGameState);
    window.display();
}

void Game_Window::run_level(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    handleCollisions(a_player, a_scene, currentGameState);
    draw_background(a_scene, currentGameState);
    draw_scene(a_player, a_scene, currentGameState);
    draw_score(a_player.get_level_score());
    animate_balls(a_scene);
    window.display();
}

void Game_Window::run_scoreboard_screen(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    draw_background(a_scene, currentGameState);
    draw_scene(a_player, a_scene, currentGameState);
    window.display();
}

void Game_Window::restart(Scene& a_scene)
{
    window.clear();
    a_scene.reset();
}

bool Game_Window::close_window_check(Event const& event)
{
    if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
    {
        window.close();
        return true;
    }
    return false;
}

void Game_Window::game_win_screen()
{
    illustrator->draw_win_screen(window);
}

void Game_Window::game_over_screen()
{
    illustrator->draw_game_over_screen(window);
}

void Game_Window::animate_balls(Scene& a_scene)
{
    auto& balls = a_scene.get_balls();
    for (const auto& ballPtr : balls)
    {
        animator->animate_ball(*ballPtr);
    }
}

void Game_Window::animate_paddle_right(Scene& a_scene)
{
    animator->animate_paddle_right(a_scene.get_paddle(), clock);
}

void Game_Window::animate_paddle_left(Scene& a_scene)
{
    animator->animate_paddle_left(a_scene.get_paddle(), clock);
}

void Game_Window::animate_paddle_stop(Scene& a_scene)
{
    animator->animate_paddle_stop(a_scene.get_paddle());
}

bool Game_Window::pause_game(GameState& currentGameState)
{
    Event event;
    while(currentGameState == GameState::Paused)
    {
        draw_pause_text();
        window.display();
        while (window.pollEvent(event))
        {   
            if(close_window_check(event))
            {
                return false;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                currentGameState = GameState::Level;
                break;
            }
        }
    }
    return true;
}

void Game_Window::paddle_movement_control(Scene& a_scene, Event const& event, GameState& currentGameState)
{
    Paddle& paddle = a_scene.get_paddle();
    auto& balls = a_scene.get_balls();
    if (event.type == sf::Event::KeyPressed)
    {
        if (!(paddle.started()))
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                for(auto& ballPtr : balls)
                {
                    ballPtr->ball_start();
                }
                paddle.paddle_start();
            }
            else if(event.key.code == sf::Keyboard::Right)
            {
                animate_paddle_right(a_scene);
                for(auto& ballPtr : balls)
                {
                    ballPtr->setPosition(paddle.getPosition().x + paddle.getSize().x / 2.5, SCREEN_HEIGHT - 70);
                }
            }
            else if(event.key.code == sf::Keyboard::Left)
            {
                animate_paddle_left(a_scene);
                for(auto& ballPtr : balls)
                {
                    ballPtr->setPosition(paddle.getPosition().x + paddle.getSize().x / 2.5, SCREEN_HEIGHT - 70);
                }
            }
        }
        else
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                currentGameState = GameState::Paused;
                if(!pause_game(currentGameState))
                {
                    a_scene.stop_scene_music();
                }
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                animate_paddle_right(a_scene);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                animate_paddle_left(a_scene);
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased && (paddle.started()))
    {
        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
        {
            animate_paddle_stop(a_scene);
        }
    }
}

bool Game_Window::title_screen_button_click_handler(Scene& a_scene, Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));


        auto const& buttons = a_scene.get_buttons(); 

        Button& button1 = *buttons.at(0);
        Button& button2 = *buttons.at(1);

        if (button1.getBounds().contains(mousePosition))
        {                    
            return true;
        }
        else if (button2.getBounds().contains(mousePosition))
        {
            window.close();
        }
    }
    return false;
}

bool Game_Window::input_name(std::string& a_name)
{
    if(illustrator->draw_input_name_screen(a_name, window))
    {
        return true;
    }
    return false;
}        

void Game_Window::paddle_out_of_bounds_handler(Scene& a_scene)
{
    Paddle& pad = a_scene.get_paddle();

    FloatRect paddleBounds = pad.getGlobalBounds();
    FloatRect borderBounds = (*a_scene.get_border()).getGlobalBounds();

    float newY = pad.getPosition().y;
    float newXL = borderBounds.left + 5.0f;
    float newXR = borderBounds.left + borderBounds.width - paddleBounds.width - 5.0f;

    if (paddleBounds.left < borderBounds.left)
    {
        pad.setPosition(newXL,newY);
    }
    else if (paddleBounds.left + paddleBounds.width > borderBounds.left + borderBounds.width)
    {
        pad.setPosition(newXR,newY);
    }
}

bool Game_Window::pressed_any_key(Event const& event)
{
    if ((event.type == Event::KeyPressed && event.key.code != Keyboard::Escape))
    {
        return true;
    }
    return false;
}

void Game_Window::level_collisions_handler(Player& a_player, Scene& a_scene)
{
    Paddle& pad = a_scene.get_paddle();
    auto& blocks = a_scene.get_blocks(); 
    auto& balls = a_scene.get_balls();

    paddle_out_of_bounds_handler(a_scene);

    for (const auto& ballPtr : balls)
    {
        if(ballPtr->isVanished())
        {
            continue;
        }

        for (auto& block : blocks)
        {   
            if(block->isVanished())//slight optimization
            {
                continue;
            }
            if(check_collision(*ballPtr, *block))
            {
                a_player.add_score(block->getScoreValue(a_scene.get_level_number()));
                ball_block_collision_handler(*block, *ballPtr);//will vanish a block
            }
        }

        ball_window_collision_handler(*ballPtr, window);    
        ball_paddle_collision_handler(*ballPtr,pad);

        if(ball_kill_zone_collision_handler(*ballPtr, *a_scene.get_kill_zone()))  // will vanish a ball , wont delete it from the vector
        {
            a_player.hit();
            ballPtr->reset();
            pad.reset();
        }
    }
}

void Game_Window::handleCollisions(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            break;
        case GameState::Level:
            level_collisions_handler(a_player, a_scene);
            break;
        case GameState::ScoreBoard:
            break;
        case GameState::Paused:
            break;
    }
}

bool Game_Window::isOpen()
{
    return window.isOpen();
}

RenderWindow& Game_Window::getWindow()
{
    return window;
}

} // namespace arkanoid
