#include "../inc/paddle.hpp"
namespace arkanoid
{

Paddle::Paddle()
{
    paddle = std::make_unique<RectangleShape>(Vector2f(100.0f, 20.0f));

    paddle->setFillColor(Color::Blue);
    paddle->setPosition(400.0f, 550.0f);
    speed = 15.0f;
    velocity = Vector2f(0.0f, 0.0f);
}

Vector2f& Paddle::getVelocity()
{
    return velocity;
}

FloatRect Paddle::getGlobalBounds()
{
    return paddle->getGlobalBounds();
}

const RectangleShape& Paddle::getShape() const
{
    return *paddle;
}

Vector2f Paddle::getPosition()
{
    return paddle->getPosition();
}

void Paddle::setPosition(float a_x, float a_y)
{
    paddle->setPosition(a_x, a_y);
}

void Paddle::move(Vector2f a_v)
{
    paddle->move(a_v);
}

void Paddle::setPosition(Vector2f a_v)
{
    paddle->setPosition(a_v);
}

void Paddle::right()
{
    velocity.x = speed; 
}

void Paddle::left()
{   
    velocity.x = -speed;
}

void Paddle::stop()
{
    velocity.x = 0;
}

}//namepsace arkanoid