#include "../inc/paddle.hpp"
namespace arkanoid
{

Paddle::Paddle()
{
    paddle = std::make_unique<sf::RectangleShape>(sf::Vector2f(100.0f, 20.0f));

    paddle->setFillColor(sf::Color::Blue);
    paddle->setPosition(400.0f, 550.0f);
    speed = 10.0f;
    velocity = sf::Vector2f(speed, 0.0f);
}

sf::RectangleShape& Paddle::operator*()
{
    return *paddle;
}

sf::Vector2f& Paddle::getVelocity()
{
    return velocity;
}

void Paddle::right()
{
    velocity.x = speed;
}

void Paddle::left()
{
    velocity.x = -speed;
}

}//namepsace arkanoid