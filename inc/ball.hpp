#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <random>

namespace arkanoid
{
class Ball
{
public:
    Ball();
    sf::Vector2f& getVelocity();
    void setVelocity(sf::Vector2f);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f const& getPosition();
    void vanish();
    const sf::CircleShape& getShape() const;
    void ball_start();
    void ball_slow_down();
    void ball_return_normal_speed();
    bool started();
    bool is_slow() const;
    void non_elastic_vertical();
    void reset();
    void elastic_vertical();
    void elastic_horizontal();
    bool isVanished();
    void move(sf::Vector2f);
    void move(float, float);
    void set_color(sf::Color);
    void setPosition(sf::Vector2f);
    void setPosition(float, float);
    float getRadius();
    ~Ball() = default;
    
private:
    std::unique_ptr<sf::CircleShape> shape;
    std::unique_ptr<sf::Texture> ballTexture;
    sf::Vector2f velocity;
    float speed;
    bool is_slowed;
    bool start;
    bool vanished;
};

float magnitude(sf::Vector2f const&);
float toRadians(float);

}//namespace arkanoid
#endif