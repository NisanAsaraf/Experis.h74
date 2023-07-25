#include "paddle.hpp"
namespace arkanoid
{
using namespace sf;
Paddle::Paddle()
{
    paddle = std::make_unique<RectangleShape>(Vector2f(100.0f, 20.0f));
    start = false;
    paddleTexture    = std::make_unique<Texture>();

    if (!(*paddleTexture).loadFromFile("../../assets/textures/Breakout/PNG/49-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    paddle->setTexture(&(*paddleTexture));
    paddle->setPosition(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 50);
    max_speed = 40.0f;
    acceleration = 10.0f;
    velocity = Vector2f(0.0f, 0.0f);
}

void Paddle::right(Clock a_clock)
{
    Time deltaTime = a_clock.restart();
    float timeDeltaSeconds = deltaTime.asSeconds();
    if(velocity.x < max_speed)
    {
        float newVelocity = velocity.x + (acceleration * timeDeltaSeconds * timeDeltaSeconds);
        velocity.x = std::min(newVelocity, max_speed);
    }
}

void Paddle::left(Clock a_clock)
{   
    Time deltaTime = a_clock.restart();
    float timeDeltaSeconds = deltaTime.asSeconds();
    if(velocity.x > -max_speed)
    {
        float newVelocity = velocity.x - (acceleration * timeDeltaSeconds * timeDeltaSeconds);
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
    if (!(*paddleTexture).loadFromFile("../../assets/textures/Breakout/PNG/47-Breakout-Tiles.png"))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
    paddle->setSize(Vector2f(150.0f, 20.0f));
}

}//namepsace arkanoid