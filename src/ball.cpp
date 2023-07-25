#include "ball.hpp"
#include <cmath>

namespace arkanoid
{
    using namespace sf;

    Ball::Ball()
    {
        shape = std::make_unique<CircleShape>(10.0f);
        shape->setPosition(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT - 70);
        vanished = false;
        speed = 5.0f;
        ballTexture = std::make_unique<Texture>();
        if (!(*ballTexture).loadFromFile("../../assets/textures/Breakout/PNG/58-Breakout-Tiles.png"))
        {
            throw std::runtime_error("Failed to load font from file.");
        }

        shape->setTexture(&(*ballTexture));
        velocity = Vector2f(0,0);
        start = false;
        is_slowed = false;
    }

    void Ball::ball_start()
    {
        std::uniform_real_distribution<float> dist(60.0f, 120.0f);
        std::random_device rd;
        std::mt19937 gen(rd());

        float angle_rad = toRadians(dist(gen));
        float magnitude = -speed;
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
        shape->setPosition(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT - 70);
        velocity = Vector2f(0,0);
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

    void Ball::non_elastic_vertical()
    {
        velocity.y *= -1.1;
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

    void Ball::ball_slow_down()
    {
        velocity *= 0.5f;
        is_slowed = true;
    }

    bool Ball::is_slow() const
    {
        return is_slowed;
    }

    void Ball::ball_return_normal_speed()
    {
        velocity *= 2.0f;
        is_slowed = false;
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
