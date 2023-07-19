#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


namespace arkanoid
{
using namespace sf;

class RandomColorGenerator
{
public:
    static Color getRandomColor()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return Color(dis(gen), dis(gen), dis(gen));
    } 
};

class Ball
{
public:
    Ball();
    Vector2f& getVelocity();
    FloatRect getGlobalBounds();
    Vector2f const& getPosition();
    void vanish();
    const CircleShape& getShape() const;
    void ball_start();
    bool started();
    void reset();
    void elastic_vertical();
    void elastic_horizontal();
    bool isVanished();
    void move(Vector2f);
    void move(float, float);
    void set_color(Color);
    void setPosition(Vector2f);
    void setPosition(float, float);
    float getRadius();
    ~Ball() = default;
    
private:
    std::unique_ptr<CircleShape> shape;
    Vector2f velocity;
    bool start;
    bool vanished;
};

float magnitude(Vector2f const&);
float toRadians(float);

}//namespace arkanoid
#endif