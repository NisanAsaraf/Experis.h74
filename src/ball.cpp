#include "../inc/ball.hpp"
#include <cmath>

namespace arkanoid
{
    using namespace sf;

    Ball::Ball()
    {
        shape = std::make_unique<CircleShape>(10.0f);
        shape->setPosition(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT - 70);
        vanished = false;

        //Color randomColor = RandomColorGenerator::getRandomColor();
        shape->setFillColor(Color::White);
        velocity = Vector2f(0,0);
        start = false;
    }

    void Ball::ball_start()
    {
        std::uniform_real_distribution<float> dist(60.0f, 120.0f);
        std::random_device rd;
        std::mt19937 gen(rd());

        float angle_rad = toRadians(dist(gen));
        float magnitude = -5.0f;
        float vx = magnitude * cos(angle_rad);
        float vy = magnitude * sin(angle_rad);

        velocity = sf::Vector2f(vx,vy);
        start = true;
    }

    bool Ball::started()
    {
        return start;
    }

    void Ball::reset()
    {
        shape->setPosition(400.0f, 550.0f);
        start = false;
    }

    const CircleShape& Ball::getShape() const 
    {
        return *shape;
    }

    void Ball::move(Vector2f a_v)
    {
        shape->move(a_v);
    }

    void Ball::move(float a_x, float a_y)
    {
        shape->move(a_x,a_y);
    }

    void Ball::elastic_horizontal()
    {
        velocity.x *= -1;
    }

    void Ball::setVelocity(Vector2f a_v)
    {   
        velocity = a_v;
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

    FloatRect Ball::getGlobalBounds()
    {
        return shape->getGlobalBounds();
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

    bool Ball::isVanished()
    {
        return vanished;
    }

    void Ball::vanish()
    {
        shape->setFillColor(Color::Transparent);
        shape->setRadius(0);
        shape->setPosition(0,0);
        velocity = Vector2f(0,0);
        vanished = true;
    }
    
    float magnitude(const sf::Vector2f& v) 
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    float toRadians(float degrees) 
    {
        return degrees * (3.1416 / 180.0f);
    }

}//namespace arkanoid
