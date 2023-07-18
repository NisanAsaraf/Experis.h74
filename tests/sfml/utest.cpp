#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

namespace sfml_test
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
        shape = std::make_unique<CircleShape>(20.0f);
        shape->setPosition(400.0f, 300.0f);
        Color randomColor = RandomColorGenerator::getRandomColor();
        shape->setFillColor(randomColor);

        std::uniform_real_distribution<float> dist(-0.1f, 0.1f);

        std::random_device rd;
        std::mt19937 gen(rd());

        float randomX = dist(gen);
        float randomY = dist(gen);

        Velocity = sf::Vector2f(randomX,randomY);
    }

    CircleShape& operator*()
    {
        return *shape;
    }

    Vector2f& getVelocity()
    {
        return Velocity;
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
    Vector2f Velocity;
};

class Game_Window
{
public:
    Game_Window() : window(VideoMode(800, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close)
    {
        
        float borderWidth = window.getSize().x - 10.0f ;
        float borderHeight = window.getSize().y - 10.0f ;
        sf::Color Teal(0, 128, 128);

        border = std::make_unique<sf::RectangleShape>(Vector2f(borderWidth, borderHeight));
        border->setFillColor(Color::Transparent);

        border->setPosition(5.0f, 5.0f);
        border->setOutlineThickness(5.0f);
        border->setOutlineColor(Teal);
        spawn_ball();
    
    }

    ~Game_Window() = default;

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
            animate();

            window.display();
        }
    }

    void animate()
    {
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *(ballPtr.get());
            CircleShape& shape = *ball;
            Vector2f& velocity = ball.getVelocity();
            shape.move(velocity);
        }
    }

    void draw_shapes()
    {
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
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                spawn_ball();
            }
        }
    }

    void handleCollisions()
    {
        for (const auto& ballPtr : balls)
        {
            sf::Vector2f circlePosition = ballPtr->getPosition();
            sf::Vector2f& circleVelocity = ballPtr->getVelocity();
            bool collision = false;
            float circleRadius = ballPtr->getRadius();

            sf::Vector2u windowSize = window.getSize();

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
    std::vector<std::unique_ptr<Ball>> balls;
};

} // namespace sfml_test

int main()
{
    sfml_test::Game_Window window;
    window.run();

    return 0;
}
