#include <SFML/Graphics.hpp>
namespace sfml_test
{


    class Make_window
    {
    public:
        Make_window() : window(sf::VideoMode(800, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close)
        {

            float borderWidth = window.getSize().x - 10.0f ;
            float borderHeight = window.getSize().y - 10.0f ;

            border = std::make_unique<sf::RectangleShape>(sf::Vector2f(borderWidth, borderHeight));
            border->setFillColor(sf::Color::Transparent);

            border->setPosition(5.0f, 5.0f);
            border->setFillColor(sf::Color::Transparent);
            border->setOutlineThickness(5.0f);

            border->setOutlineColor(sf::Color::Blue);

            circle = std::make_unique<sf::CircleShape>(50.0f);
            circle->setPosition(400.0f, 300.0f);
            circle->setFillColor(sf::Color::Red);
            circleVelocity = sf::Vector2f(0.05, 0.02f);
        }

        void run()
        {
            while (window.isOpen())
            {
                processEvents();
                circle->move(circleVelocity);
                handleCollisions();
                window.clear(sf::Color::Black);
                window.draw(*border);
                window.draw(*circle);
                window.display(); 
            }
        }

        ~Make_window()
        {
           
        }

    private:
        sf::RenderWindow window;
        std::unique_ptr<sf::CircleShape> circle;
        std::unique_ptr<sf::RectangleShape> border;
        sf::Vector2f circleVelocity;

        void processEvents()
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    break;
                }
            }
        }



        void handleCollisions()
        {
            sf::Vector2f circlePosition = circle->getPosition();
            float circleRadius = circle->getRadius();

            sf::Vector2u windowSize = window.getSize();

            if (circlePosition.x < 0 || circlePosition.x + 2 * circleRadius > windowSize.x)
            {
                circleVelocity.x = -circleVelocity.x;
            }

            if (circlePosition.y < 0 || circlePosition.y + 2 * circleRadius > windowSize.y)
            {
                circleVelocity.y = -circleVelocity.y;
            }
        }
    };

} // namespace sfml_test

int main()
{
    sfml_test::Make_window window;
    window.run();

    return 0;
}
