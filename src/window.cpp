#include "../inc/window.hpp"
#include <exception>
#include <memory>
#include <fstream>
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

void Game_Window::draw_background_title_screen(Scene& m_scene)
{
    Title_Screen* title_screen_ptr = dynamic_cast<Title_Screen*>(&m_scene);
    illustrator->draw_BG_title(*title_screen_ptr,window);
}

void Game_Window::draw_background_level_one(Scene& m_scene)
{
    Level_One* level_1 = dynamic_cast<Level_One*>(&m_scene);
    illustrator->draw_BG_level(*level_1,window);
}

void Game_Window::Game_Window::draw_background_score_board(Scene& m_scene)
{
    Score_Board* score_scrn = dynamic_cast<Score_Board*>(&m_scene);
    illustrator->draw_BG_scoreboard(*score_scrn,window);
}

void Game_Window::draw_background(Scene& a_scene, GameState& currentGameState)
{
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            draw_background_title_screen(a_scene);
            break;

        case GameState::Level1:
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
    Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(&a_scene);
    illustrator->draw_title_screen(*title_scrn, window);
}

void Game_Window::draw_level_one(Player& a_player, Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    illustrator->draw_level_one(*level_one, window);
    draw_hearts(a_player.get_lives());
}

void Game_Window::draw_scoreboard(Scene& a_scene)
{
    Score_Board* score_scrn = dynamic_cast<Score_Board*>(&a_scene);
    Illustrator ilustrator;
    ilustrator.draw_scoreboard(*score_scrn, window);
}

void Game_Window::draw_scene(Player& a_player,Scene& a_scene, GameState& currentGameState)
{  
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            draw_title_screen(a_scene);
            break;
        case GameState::Level1:
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

void Game_Window::run_level_one(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    handleCollisions(a_player, a_scene, currentGameState);
    draw_background(a_scene, currentGameState);
    draw_scene(a_player, a_scene, currentGameState);
    draw_score(a_player.get_score());
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
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    level_one->reset();
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
    Illustrator illustrator;
    illustrator.draw_win_screen(window);
}

void Game_Window::game_over_screen()
{
    Illustrator illustrator;
    illustrator.draw_game_over_screen(window);
}

void Game_Window::animate_balls(Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    auto balls = level_one->get_balls();
    for (const auto& ballPtr : balls)
    {
        animator->animate_ball(*ballPtr);
    }
}

void Game_Window::animate_paddle_right(Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    animator->animate_paddle_right(level_one->get_paddle(), clock);
}

void Game_Window::animate_paddle_left(Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    animator->animate_paddle_left(level_one->get_paddle(), clock);
}

void Game_Window::animate_paddle_stop(Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    animator->animate_paddle_stop(level_one->get_paddle());
}

void Game_Window::pause_game(GameState& currentGameState)
{
    Event event;
    GameState previousGameState = currentGameState;
    while(currentGameState == GameState::Paused)
    {
        draw_pause_text();
        window.display();
        while (window.pollEvent(event))
        {   
            close_window_check(event);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                currentGameState = previousGameState;
                break;
            }
        }
    }
}

void Game_Window::paddle_movement_control(Scene& a_scene, Event const& event, GameState& currentGameState)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    Paddle& paddle = level_one->get_paddle();
    auto& balls = level_one->get_balls();

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space && !(paddle.started()))
        {
            for(auto& ballPtr : balls)
            {
                ballPtr->ball_start();
            }
            level_one->get_paddle().paddle_start();
        }
        else if (event.key.code == sf::Keyboard::Space && (paddle.started()))
        {
            currentGameState = GameState::Paused;
            pause_game(currentGameState);
        }
        else if (event.key.code == sf::Keyboard::Right && (paddle.started()))
        {
            animate_paddle_right(a_scene);
        }
        else if (event.key.code == sf::Keyboard::Left && (paddle.started()))
        {
            animate_paddle_left(a_scene);
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

        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(&a_scene);
        auto const& buttons = title_scrn->get_vector(); 

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

std::string Game_Window::input_name()
{
    return illustrator->draw_input_name_screen(window);
}        

void Game_Window::paddle_out_of_bounds_handler(Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    Paddle& pad = level_one->get_paddle();

    FloatRect paddleBounds = pad.getGlobalBounds();
    FloatRect borderBounds = (*level_one->get_border()).getGlobalBounds();

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

void Game_Window::level_one_collisions_handler(Player& a_player, Scene& a_scene)
{
    Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
    Paddle& pad = level_one->get_paddle();
    auto& blocks = level_one->get_vector(); 
    auto& balls = level_one->get_balls();

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
                a_player.add_score(40);
                ball_block_collision_handler(*block, *ballPtr);//will vanish a block
            }
        }

        ball_window_collision_handler(*ballPtr, window);    
        ball_paddle_collision_handler(*ballPtr,pad);

        if(ball_kill_zone_collision_handler(*ballPtr, *level_one->get_kill_zone()))  // will vanish a ball , wont delete it from the vector
        {
            a_player.hit();
            if(a_player.is_dead())
            {
                game_over_screen();
            }
            ballPtr->reset();
            //paddle_reset();

            //balls.erase(balls.begin()); // will delete the pointer from the vector, the smart pointer will handle the memory
            //spawn_ball();
        }
    }
}

void Game_Window::handleCollisions(Player& a_player, Scene& a_scene, GameState& currentGameState)
{
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            break;
        case GameState::Level1:
            level_one_collisions_handler(a_player, a_scene);
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
