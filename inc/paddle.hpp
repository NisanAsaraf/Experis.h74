#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{

class Paddle
{
public:
    Paddle();

    sf::RectangleShape& operator*();

    sf::Vector2f& getVelocity();

    void left();
    void right();
    void stop();

private:
    std::unique_ptr<sf::RectangleShape> paddle;
    sf::Vector2f velocity;
    float speed;

};

}//namespace arkanoid
#endif //PADDLE_H