#include "../inc/paddle.hpp"
#include <vector>
#include <random>
#include <iostream>

namespace arkanoid
{
using namespace sf;

class RandomColorGenerator
{
public:
    static Color getRandomColor()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return Color(dis(gen), dis(gen), dis(gen));
    } 
};

class Ball
{
public:

    Ball()
    {
        shape = std::make_unique<CircleShape>(10.0f);
        shape->setPosition(400.0f, 300.0f);
        Color randomColor = RandomColorGenerator::getRandomColor();
        shape->setFillColor(randomColor);

        std::uniform_real_distribution<float> dist(-2.0f, 2.0f);

        std::random_device rd;
        std::mt19937 gen(rd());

        float randomX = dist(gen);
        float randomY = dist(gen);

        velocity = sf::Vector2f(randomX,randomY);
    }

    CircleShape& operator*()
    {
        return *shape;
    }

    Vector2f& getVelocity()
    {
        return velocity;
    }

    Vector2f const& getPosition()
    {
        return shape->getPosition();
    }

    void set_color(Color a_color)
    {
        shape->setFillColor(a_color);
    }

    void setPosition(Vector2f vel)
    {
        shape->setPosition(vel.x ,vel.y);
    }

    void setPosition(float x, float y)
    {
        shape->setPosition(x ,y);
    }
    
    float getRadius()
    {
        return shape->getRadius();
    }

    ~Ball() = default;

private:
    std::unique_ptr<CircleShape> shape;
    Vector2f velocity;
};

class Game_Window
{
public:
    Game_Window() : window(VideoMode(800, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close)
    { 
        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        make_border();
        make_paddle();
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
            animate_balls();

            window.display();
        }
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

    void handleCollisions()
    {
        Vector2u windowSize = window.getSize();
        FloatRect borderBounds = (*border).getGlobalBounds();
        FloatRect windowBounds(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(windowSize.x -5.0f, windowSize.y - 5.0f));
        FloatRect paddleBounds = (**paddle).getGlobalBounds();
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

        for (const auto& ballPtr : balls)
        {
            CircleShape& ball = **ballPtr;
            RectangleShape& pad = **paddle;
            Vector2f circlePosition = ballPtr->getPosition();
            Vector2f& circleVelocity = ballPtr->getVelocity();
            bool collision = false;
            float circleRadius = ballPtr->getRadius();

            FloatRect ballBounds = ball.getGlobalBounds();
            FloatRect paddleBounds = pad.getGlobalBounds();

            float overlapX = std::min(ballBounds.left + ballBounds.width, paddleBounds.left + paddleBounds.width) - std::max(ballBounds.left, paddleBounds.left);                
            float overlapY = std::min(ballBounds.top + ballBounds.height, paddleBounds.top + paddleBounds.height) -  std::max(ballBounds.top, paddleBounds.top);            

            if (circlePosition.x <= 0 || circlePosition.x + 2.5 * circleRadius > windowSize.x)
            {
                circleVelocity.x = -circleVelocity.x;
                collision = true;
            }

            if (circlePosition.y <= 0 || circlePosition.y + 2.5 * circleRadius > windowSize.y)
            {
                circleVelocity.y = -circleVelocity.y;
                collision = true;
            }

            if (ball.getGlobalBounds().intersects(pad.getGlobalBounds()))
            {
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
                    circleVelocity.x *= -1.0;
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
                    circleVelocity.y *= -1.0;
                }
            }

            if(collision)
            {
                Color randomColor = RandomColorGenerator::getRandomColor();
                ballPtr->set_color(randomColor);
            }
        }
    }

private:
    sf::RenderWindow window;
    std::unique_ptr<RectangleShape> border;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;
};

} // namespace arkanoid

int main()
{
    arkanoid::Game_Window window;
    window.run();

    return 0;
}
