#include "../inc/ball.hpp"

namespace arkanoid
{
    using namespace sf;

    Ball::Ball()
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

    CircleShape& Ball::operator*()
    {
        return *shape;
    }

    void Ball::elastic_horizontal()
    {
        velocity.x *= -1;
    }

    void Ball::elastic_vertical()
    {
        velocity.y *= -1;
    }
    
    Vector2f& Ball::getVelocity()
    {
        return velocity;
    }

    Vector2f const& Ball::getPosition()
    {
        return shape->getPosition();
    }

    void Ball::set_color(Color a_color)
    {
        shape->setFillColor(a_color);
    }

    void Ball::setPosition(Vector2f vel)
    {
        shape->setPosition(vel.x ,vel.y);
    }

    void Ball::setPosition(float x, float y)
    {
        shape->setPosition(x ,y);
    }
    
    float Ball::getRadius()
    {
        return shape->getRadius();
    }

    
}//namespace arkanoid
