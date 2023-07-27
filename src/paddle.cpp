#include "paddle.hpp"
namespace arkanoid
{
using namespace sf;
Paddle::Paddle()
{
    paddle = std::make_unique<RectangleShape>(Vector2f(100.0f, 20.0f));
    start = false;
    paddleTexture    = std::make_unique<Texture>();

    if (!(*paddleTexture).loadFromFile("../../assets/textures/Breakout/PNG/paddle.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    paddle->setTexture(&(*paddleTexture));
    paddle->setPosition(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 50);
    max_speed = 40.0f;
    min_speed = 20.0f;
    acceleration = 40.0f;
    velocity = Vector2f(min_speed, 0.0f);
}

void Paddle::right()
{
    float timeDeltaSeconds = 30.0f/64.0f;
    if(velocity.x < max_speed)
    {
        float newVelocity = min_speed + velocity.x + (acceleration * timeDeltaSeconds);
        velocity.x = std::min(newVelocity, max_speed);
    }
}

void Paddle::left()
{   

    float timeDeltaSeconds = 30.0f/64.0f;
    if(velocity.x > -max_speed)
    {
        float newVelocity = -1.0 * min_speed + velocity.x - (acceleration * timeDeltaSeconds);
        velocity.x = std::max(newVelocity, -max_speed);
    }

}

Vector2f Paddle::getSize() const
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

bool Paddle::started() const
{
    return start;
}

void Paddle::reset()
{
    paddle->setPosition(350.0f, 550.0f);
    start = false;
}

Vector2f Paddle::getVelocity() const
{
    return velocity;
}

FloatRect Paddle::getGlobalBounds() const
{
    return paddle->getGlobalBounds();
}

const RectangleShape& Paddle::getShape() const
{
    return *paddle;
}

Vector2f Paddle::getPosition() const
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

void Paddle::upgrade_size()
{
    if (!(*paddleTexture).loadFromFile("../../assets/textures/Breakout/PNG/long_paddle.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    paddle->setSize(Vector2f(150.0f, 20.0f));
}

}//namepsace arkanoid