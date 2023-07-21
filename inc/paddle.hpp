#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "config.hpp"
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
    Vector2f getSize();
    void reset();
    const RectangleShape& getShape() const;
    void setPosition(float , float);
    void setPosition(Vector2f);
    void move(Vector2f);
    void left(Clock&);
    void right(Clock&);
    void stop();

private:
    std::unique_ptr<RectangleShape> paddle;
    std::unique_ptr<Texture> paddleTexture;
    Vector2f velocity;
    float acceleration;
    bool start;
    float max_speed;
};

}//namespace arkanoid
#endif //PADDLE_H