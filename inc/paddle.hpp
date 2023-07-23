#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "config.hpp"
namespace arkanoid
{
class Paddle
{
public:
    Paddle();
    sf::Vector2f getVelocity() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    void paddle_start();
    bool started() const;
    sf::Vector2f getSize() const;
    void reset();
    sf::RectangleShape const& getShape() const;
    void setPosition(float , float);
    void setPosition(sf::Vector2f);
    void move(sf::Vector2f);
    void left(sf::Clock);
    void right(sf::Clock);
    void stop();

private:
    std::unique_ptr<sf::RectangleShape> paddle;
    std::unique_ptr<sf::Texture> paddleTexture;
    sf::Vector2f velocity;
    float acceleration;
    bool start;
    float max_speed;
};

}//namespace arkanoid
#endif //PADDLE_H