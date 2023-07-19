#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{
using namespace sf;
class Paddle
{
public:
    Paddle();
    Vector2f& getVelocity();
    FloatRect getGlobalBounds();
    Vector2f getPosition();
    void paddle_start();
    bool started();
    void reset();
    const RectangleShape& getShape() const;
    void setPosition(float , float);
    void setPosition(Vector2f);
    void move(Vector2f);
    void left();
    void right();
    void stop();

private:
    std::unique_ptr<RectangleShape> paddle;
    Vector2f velocity;
    bool start;
    float speed;
};

}//namespace arkanoid
#endif //PADDLE_H