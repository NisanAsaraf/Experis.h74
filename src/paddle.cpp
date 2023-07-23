#include "../inc/paddle.hpp"
namespace arkanoid
{

Paddle::Paddle()
{
    paddle = std::make_unique<RectangleShape>(Vector2f(100.0f, 20.0f));
    start = false;
    paddleTexture    = std::make_unique<Texture>();

    if (!(*paddleTexture).loadFromFile("/home/nisan/Experis.h74/assets/textures/Breakout/PNG/49-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    paddle->setTexture(&(*paddleTexture));
    paddle->setPosition(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 50);
    max_speed = 25.0f;
    acceleration = 50.0f;
    velocity = Vector2f(0.0f, 0.0f);
}

void Paddle::right(Clock a_clock)
{
    Time deltaTime = a_clock.restart();
    float timeDeltaSeconds = deltaTime.asSeconds();
    if(velocity.x < max_speed)
    {
        float newVelocity = velocity.x + (acceleration * timeDeltaSeconds);
        velocity.x = std::min(newVelocity, max_speed);
    }
}

void Paddle::left(Clock a_clock)
{   
    Time deltaTime = a_clock.restart();
    float timeDeltaSeconds = deltaTime.asSeconds();
    if(velocity.x > -max_speed)
    {
        float newVelocity = velocity.x - (acceleration * timeDeltaSeconds);
        velocity.x = std::max(newVelocity, -max_speed);
    }
}

Vector2f Paddle::getSize()
{
    return paddle->getSize();
}

void Paddle::stop()
{
    velocity.x = 0;
}


void Paddle::paddle_start()
{
    start = true;
}

bool Paddle::started()
{
    return start;
}

void Paddle::reset()
{
    paddle->setPosition(350.0f, 550.0f);
    start = false;
}

Vector2f Paddle::getVelocity()
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

}//namepsace arkanoid