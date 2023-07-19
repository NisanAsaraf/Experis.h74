#include "../inc/paddle.hpp"
#include "../inc/levels.hpp"
#include "../inc/ball.hpp"
#include "../inc/collisions.hpp"
#include <vector>
#include <random>

namespace arkanoid
{
using namespace sf;

class Game_Window
{
public:
    Game_Window() : window(VideoMode(800, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close)
    { 
        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        make_border();
        make_paddle();
        make_level_one();
        spawn_ball();
    }

    ~Game_Window() = default;

    void make_paddle()
    {
        paddle = std::make_unique<Paddle>();
    }

    void make_border()
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

    void spawn_ball()
    {
        balls.emplace_back(std::make_unique<Ball>());
    }

    void run()
    {
        while (window.isOpen())
        {
            processEvents();

            handleCollisions();

            window.clear(Color(255, 253, 208));
            window.draw(*border);

            draw_shapes();
            draw_level();
            animate_balls();

            window.display();
        }
    }

    void make_level_one()
    {
        level = std::make_unique<Level_One>(3, 5);
    }

    void animate_balls()
    {
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *(ballPtr.get());
            CircleShape& shape = *ball;
            Vector2f& velocity = ball.getVelocity();
            shape.move(velocity);
        }
    }

    void animate_paddle_right()
    {
        Paddle& pad = *paddle;
        RectangleShape& shape = *pad;
        pad.right();
        Vector2f& velocity = pad.getVelocity();
        shape.move(velocity);
    }

    void animate_paddle_left()
    {
        Paddle& pad = *paddle;
        RectangleShape& shape = *pad;
        pad.left();
        Vector2f& velocity = pad.getVelocity();
        shape.move(velocity);
    }

    void animate_paddle_stop()
    {
        Paddle& pad = *paddle;
        RectangleShape& shape = *pad;
        pad.stop();
        Vector2f& velocity = pad.getVelocity();
        shape.move(velocity);
    }

    void draw_shapes()
    {
        Paddle& pad = *paddle;
        window.draw(*pad);
        
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *(ballPtr.get());
            window.draw(*ball); 
        }
    }

    void draw_level()
    {
        std::vector<std::unique_ptr<sf::RectangleShape>> const& blocks = level->get_blocks(); 
        for (auto& block : blocks)
        { 
            window.draw(*block);
        }
    }

    void processEvents()
    {
        sf::Event event;
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

    void paddle_out_of_bounds_handler()
    {
        FloatRect paddleBounds = (**paddle).getGlobalBounds();
        FloatRect borderBounds = (*border).getGlobalBounds();
        float newY = (**paddle).getPosition().y;
        float newXL = borderBounds.left + 5.0f;
        float newXR = borderBounds.left + borderBounds.width - paddleBounds.width - 5.0f;

        if (paddleBounds.left < borderBounds.left)
        {
            (**paddle).setPosition(newXL,newY);
        }
        else if (paddleBounds.left + paddleBounds.width > borderBounds.left + borderBounds.width)
        {
            (**paddle).setPosition(newXR,newY);
        }
    }

    void handleCollisions()
    {
        Vector2u windowSize = window.getSize();
        FloatRect windowBounds(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(windowSize.x -5.0f, windowSize.y - 5.0f));
        FloatRect paddleBounds = (**paddle).getGlobalBounds();
        std::vector<std::unique_ptr<sf::RectangleShape>>& blocks = level->get_blocks(); 

        paddle_out_of_bounds_handler();

        for (const auto& ballPtr : balls)
        {
            CircleShape& ball = **ballPtr;
            RectangleShape& pad = **paddle;

            Vector2f ballPosition = ballPtr->getPosition();

            float ballRadius = ballPtr->getRadius();

            FloatRect ballBounds = ball.getGlobalBounds();
            
            if (ballPosition.x <= 0 || ballPosition.x + 2.5 * ballRadius > windowSize.x)
            {
                (*ballPtr).elastic_horizontal();
            }

            if (ballPosition.y <= 0 || ballPosition.y + 2.5 * ballRadius > windowSize.y)
            {
                (*ballPtr).elastic_vertical();
            }

            if (check_collision(ball, pad))
            {
                float overlapX = std::min(ballBounds.left + ballBounds.width, paddleBounds.left + paddleBounds.width) - std::max(ballBounds.left, paddleBounds.left);                
                float overlapY = std::min(ballBounds.top + ballBounds.height, paddleBounds.top + paddleBounds.height) -  std::max(ballBounds.top, paddleBounds.top); 

                if (overlapX < overlapY)
                {
                    if (ballBounds.left < paddleBounds.left)
                    {
                        ball.move(-overlapX - 0.1f, 0);
                    }
                    else
                    {
                        ball.move(overlapX + 0.1f, 0); 
                    }
                    (*ballPtr).elastic_horizontal();
                }
                else
                {
                    if (ballBounds.top < paddleBounds.top)
                    {
                        ball.move(0, -overlapY - 0.1f); 
                    }
                    else
                    {
                        ball.move(0, overlapY + 0.1f); 
                    }
                    (*ballPtr).elastic_vertical();
                }
            }
           
            for (auto& block : blocks)
            {   
                if((*block).getSize() == sf::Vector2f(0,0))//slight optimization
                {
                    continue;
                }

                if(check_collision(ball, *block))//better to not delete from the vector so to not handle all the memory problems...
                {
                    (*block).setPosition(0,0);
                    (*block).setFillColor(Color::Transparent);
                    (*block).setSize(Vector2f(0, 0));
                    (*ballPtr).elastic_vertical();
                }
            }
        }
    }

private:
    sf::RenderWindow window;
    std::unique_ptr<RectangleShape> border;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Level_One> level;

};

} // namespace arkanoid

int main()
{
    arkanoid::Game_Window window;
    window.run();

    return 0;
}
