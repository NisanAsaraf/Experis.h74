#include "window.hpp"
#include <iostream>


namespace arkanoid
{
using namespace sf;

Game_Window::Game_Window()
: window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
, "Arkanoid", Style::Titlebar | Style::Close)
{ 
    illustrator = std::make_unique<Illustrator>();
    animator = std::make_unique<Animator>();

    window.setFramerateLimit(64);
    window.setVerticalSyncEnabled(false);
    is_muted = false;
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

void Game_Window::draw_level(Player& a_player, Scene& a_scene)
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
            draw_level(a_player, a_scene);
            break;
        case GameState::ScoreBoard:
            draw_scoreboard(a_scene);
            break;
        case GameState::Paused:
            break;
    }
    draw_mute_icon_handler();
}

void Game_Window::run_title_screen(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    draw_background(a_scene, currentGameState);
    draw_scene(a_player, a_scene, currentGameState);
    window.display();
}

void Game_Window::run_level(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
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

void Game_Window::set_mute_status(bool a_mute)
{
    mute_clock.restart();
    is_muted = a_mute;
}

void Game_Window::draw_mute_icon_handler()
{   
    if(clock.getElapsedTime().asSeconds() > 2 && mute_clock.getElapsedTime().asSeconds() < 2)
    {   
        if(is_muted)
        {
            illustrator->draw_mute_icon(window);
        }
        else
        {
            illustrator->draw_sound_icon(window);
        }
    }
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
    animator->animate_paddle_right(a_scene.get_paddle());
}

void Game_Window::animate_paddle_left(Scene& a_scene)
{
    animator->animate_paddle_left(a_scene.get_paddle());
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
                    //a_scene.stop_scene_music();
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
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
        {
            animate_paddle_stop(a_scene);
        }
    }
}


bool Game_Window::title_screen_button_event_handler(Scene& a_scene, Event& event)
{   
    Vector2i mousePosition = sf::Mouse::getPosition(window);
    Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);
    auto const& buttons = a_scene.get_buttons(); 

    Button& button1 = *buttons.at(0);
    Button& button2 = *buttons.at(1);

    if (event.type == sf::Event::MouseMoved)
    { 
        if (button1.getBounds().contains(worldMousePosition))
        {
            illustrator->draw_button_hover(button1, window);
        }
        else if (button2.getBounds().contains(worldMousePosition))
        {
            illustrator->draw_button_hover(button2, window);
        }
        else
        {
            button1.on_normal();
            button2.on_normal();
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (button1.getBounds().contains(worldMousePosition))
        {                    
            return true;
        }
        else if (button2.getBounds().contains(worldMousePosition))
        {
            window.close();
        }
    }
    return false;
}

bool Game_Window::pressed_any_key(Event const& event)
{
    if ((event.type == Event::KeyPressed && event.key.code != Keyboard::Escape))
    {
        return true;
    }
    return false;
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

bool Game_Window::input_name(std::string& a_name)
{
    if(illustrator->draw_input_name_screen(a_name, window))
    {
        return true;
    }
    return false;
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
