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
    CircleShape& operator*();
    Vector2f& getVelocity();
    FloatRect getGlobalBounds();
    Vector2f const& getPosition();
    void elastic_vertical();
    void elastic_horizontal();
    
    void set_color(Color a_color);
    void setPosition(Vector2f vel);
    void setPosition(float x, float y);
    float getRadius();
    ~Ball() = default;
private:
    std::unique_ptr<CircleShape> shape;
    Vector2f velocity;
};
}//namespace arkanoid
#endif