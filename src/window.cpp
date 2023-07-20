#include "../inc/window.hpp"
#include <exception>

namespace arkanoid
{
using namespace sf;

    Game_Window::Game_Window()
    : window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
    ,"Arkanoid",Style::Titlebar | Style::Close)
    ,currentGameState(GameState::TitleScreen)
    { 
        create_player();
        if (!font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
        {
            throw std::runtime_error("Failed to load font from file.");
        }

        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        make_level_one();
    }

    void Game_Window::make_level_one()
    {
        level = std::make_unique<Level_One>(3, 5);
        currentGameState = GameState::Level1;
        make_border();
        make_kill_zone();
        make_paddle();
        spawn_ball();
    }
    
    void Game_Window::make_title_screen()
    {
    }

    void Game_Window::create_player()
    {
        player = std::make_unique<Player>();
    }

    void Game_Window::make_paddle()
    {
        paddle = std::make_unique<Paddle>();
    }

    void Game_Window::make_kill_zone()
    {
        kill_zone = std::make_unique<RectangleShape>(Vector2f(window.getSize()));
        kill_zone->setPosition(0, window.getSize().y - 10);
        kill_zone->setFillColor(Color::Transparent);
    }

    void Game_Window::make_border()
    {
        float borderWidth = window.getSize().x - 10.0f ;
        float borderHeight = window.getSize().y - 10.0f ;
        sf::Color Teal(0, 128, 128);

        border = std::make_unique<sf::RectangleShape>(Vector2f(borderWidth, borderHeight));
        border->setFillColor(Color::Transparent);

        border->setPosition(5.0f, 5.0f);
        border->setOutlineThickness(5.0f);
        border->setOutlineColor(Teal);
    }

    void Game_Window::spawn_ball()
    {
        balls.emplace_back(std::make_unique<Ball>());
    }

    void Game_Window::paddle_reset()
    {
        paddle->reset();
    }

    void Game_Window::run_level_one()
    {
        handleCollisions();
        window.clear(Color::Black);
        window.draw(*border);
        window.draw(*kill_zone);
        draw_shapes();
        draw_scene();
        animate_balls();
        draw_scoreboard();
        win_condition();
        window.display();
    }

    void Game_Window::run_title_screen()
    {
        handleCollisions();
    }

    void Game_Window::run()
    {
        while (window.isOpen())
        {   
            processEvents();
            
            switch (currentGameState)
            {
                case GameState::TitleScreen:
                    //run_title_screen();

                case GameState::Level1:
                    run_level_one();
            }
        }
    }

    void Game_Window::win_condition()
    {
        if(player->get_score() == WIN_SCORE)
        {
            game_win_screen();
        }
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
        Text text;
        Clock clk;
        Event event;
        bool quit = false;

        text.setFont(font);
        text.setString("YOU WIN!");
        text.setCharacterSize(100);
        text.setFillColor(Color::Green);
        text.setPosition(SCREEN_WIDTH/4 + 20, SCREEN_HEIGHT/3);

        while(clk.getElapsedTime().asSeconds() < 15)
        {
            window.draw(text);
            window.display();
            while (window.pollEvent(event))
            {
                quit = close_window_check(event);
            }
            if(quit)
            {
                break;
            }  
        }
        restart();
    }

    void Game_Window::game_over_screen()
    {
        Text text;
        Clock clk;
        Event event;
        bool quit = false;

        text.setFont(font);
        text.setString("GAME OVER!");
        text.setCharacterSize(100);
        text.setFillColor(Color::Red);
        text.setPosition(SCREEN_WIDTH/4 - 20, SCREEN_HEIGHT/3 );

        while(clk.getElapsedTime().asSeconds() < 30)
        {
            window.draw(text);
            window.display();
            while (window.pollEvent(event))
            {
                quit = close_window_check(event);
            }
            if(quit)
            {
                break;
            }          
        }
    }

    void Game_Window::restart()
    {
        player->reset();
        paddle_reset();
        balls.clear();
        level->reset();
        make_level_one();
        spawn_ball();
    }


    void Game_Window::animate_balls()
    {
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *ballPtr;
            ball.move(ball.getVelocity());
        }
    }

    void Game_Window::animate_paddle_right()
    {
        Paddle& pad = *paddle;
        pad.right(clock);
        pad.move(pad.getVelocity());
    }

    void Game_Window::animate_paddle_left()
    {
        Paddle& pad = *paddle;
        pad.left(clock);
        pad.move(pad.getVelocity());
    }

    void Game_Window::animate_paddle_stop()
    {
        Paddle& pad = *paddle;
        pad.stop();
        pad.move(pad.getVelocity());
    }

    void Game_Window::draw_shapes()
    {
        Paddle& pad = *paddle;
        draw_shape(pad, window);      
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *ballPtr;
            draw_shape(ball, window);
        }
    }

    void Game_Window::draw_scene()
    {
        auto const& blocks = level->get_blocks(); 
        for (auto& blockPtr : blocks)
        { 
            Block& block = *blockPtr;
            draw_shape(block, window);
        }
    }

    void Game_Window::draw_scoreboard()
    {
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(player->get_score()));

        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(30, 30);
        window.draw(scoreText);
    }

    void Game_Window::paddle_movement_control(Event const& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space && !(paddle->started()))
            {
                for(auto& ballPtr : balls)
                {
                    ballPtr->ball_start();
                }
                paddle->paddle_start();
            }
            else if (event.key.code == sf::Keyboard::Right && paddle->started())
            {
                animate_paddle_right();
            }
            else if (event.key.code == sf::Keyboard::Left && paddle->started())
            {
                animate_paddle_left();
            }
        }
        else if (event.type == sf::Event::KeyReleased && paddle->started())
        {
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
            {
                animate_paddle_stop();
            }
        }
    }
    void Game_Window::processEvents()
    {
        Event event;
        while (window.pollEvent(event))
        {
            close_window_check(event);
            paddle_movement_control(event);
        }
    }

    void Game_Window::paddle_out_of_bounds_handler()
    {
        Paddle& pad = *paddle;
        FloatRect paddleBounds = pad.getGlobalBounds();
        FloatRect borderBounds = (*border).getGlobalBounds();
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

    void Game_Window::handleCollisions()
    {
        Paddle& pad = *paddle;
        auto& blocks = level->get_blocks(); 

        paddle_out_of_bounds_handler();

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
                    player->add_score(40);
                    ball_block_collision_handler(*block, *ballPtr);//will vanish a block
                }
            }

            ball_window_collision_handler(*ballPtr, window);    
            ball_paddle_collision_handler(*ballPtr,pad);

            if(ball_kill_zone_collision_handler(*ballPtr, *kill_zone))  // will vanish a ball , wont delete it from the vector
            {
                player->hit();
                if(player->is_dead())
                {
                    game_over_screen();
                }
                ballPtr->reset();
                paddle_reset();

                balls.erase(balls.begin()); // will delete the pointer from the vector, the smart pointer will handle the memory
                spawn_ball();
            }
        }
    }
} // namespace arkanoid
