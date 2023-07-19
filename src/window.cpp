#include "../inc/window.hpp"
#include <iostream>
#include <exception>

namespace arkanoid
{
using namespace sf;

    Game_Window::Game_Window(std::string const& a_name) : window(VideoMode(800, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close)
    { 
        create_player(a_name);
        if (!font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
        {
            throw std::runtime_error("Failed to load font from file.");
        }
        
        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        make_border();
        make_paddle();
        make_level_one();
        spawn_ball();
    }

    void Game_Window::create_player(std::string const& a_name)
    {
        player = std::make_unique<Player>(a_name);
    }

    void Game_Window::make_paddle()
    {
        paddle = std::make_unique<Paddle>();
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

    void Game_Window::run()
    {
        while (window.isOpen())
        {
            processEvents();

            handleCollisions();

            window.clear(Color::Black); //cream color 
            window.draw(*border);

            draw_shapes();
            draw_level();
            animate_balls();
            draw_scoreboard();
            window.display();
        }
    }

    void Game_Window::make_level_one()
    {
        level = std::make_unique<Level_One>(3, 5);
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
        pad.right();
        pad.move(pad.getVelocity());
    }

    void Game_Window::animate_paddle_left()
    {
        Paddle& pad = *paddle;
        pad.left();
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

    void Game_Window::draw_level()
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

    void Game_Window::processEvents()
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    spawn_ball();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    animate_paddle_right();
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    animate_paddle_left();
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
                {
                    animate_paddle_stop();
                }
            }
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
            ball_window_collision_handler(*ballPtr, window);    
            ball_paddle_collision_handler(*ballPtr,pad);

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
        }
    }
} // namespace arkanoid
