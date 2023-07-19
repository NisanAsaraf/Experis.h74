#include "../inc/collisions.hpp"
#include <SFML/Graphics.hpp>

namespace arkanoid
{
 
bool check_collision(Ball& a_ball, Block& a_block)
{
    FloatRect ball_bounds = a_ball.getGlobalBounds();
    FloatRect block_bounds = a_block.getGlobalBounds();

    return ( ball_bounds.intersects(block_bounds));
}

bool check_collision(Block& a_block, Ball& a_ball)
{
    FloatRect ball_bounds = a_ball.getGlobalBounds();
    FloatRect block_bounds = a_block.getGlobalBounds();

    return ( ball_bounds.intersects(block_bounds));
}

bool check_collision(Ball& a_ball, Paddle& a_paddle)
{
    FloatRect ball_bounds = a_ball.getGlobalBounds();
    FloatRect paddle_bounds = a_paddle.getGlobalBounds();

    return ( ball_bounds.intersects(paddle_bounds));
}

bool check_collision(Paddle& a_paddle, Ball& a_ball)
{
    FloatRect ball_bounds = a_ball.getGlobalBounds();
    FloatRect paddle_bounds = a_paddle.getGlobalBounds();

    return ( ball_bounds.intersects(paddle_bounds));
}

bool check_window_collision(Shape& a_shape, RenderWindow& a_window , float a_buffer)
{
    FloatRect shape_bounds = a_shape.getGlobalBounds();
    FloatRect window_bounds(Vector2f(a_buffer, a_buffer), Vector2f(a_window.getSize().x - a_buffer, a_window.getSize().y - a_buffer));

    return (shape_bounds.intersects(window_bounds));
}

void ball_block_collision_handler(Block& a_block, Ball& a_ball)
{
    a_block.Collision();
    a_ball.elastic_vertical();
}

void ball_block_collision_handler(Ball& a_ball, Block& a_block)
{
    a_block.Collision();
    a_ball.elastic_vertical();
}

void ball_window_collision_handler(Ball& a_ball, RenderWindow& a_window)
{
    FloatRect ballBounds = a_ball.getGlobalBounds();
    auto windowSize = a_window.getSize();
    float buffer = 10.0f;

    if (ballBounds.left <= buffer || ballBounds.left + ballBounds.width >= windowSize.x - buffer)
    {
        a_ball.elastic_horizontal();
    }

    if (ballBounds.top <= buffer || ballBounds.top + ballBounds.height >= windowSize.y - buffer)
    {
        a_ball.elastic_vertical();
    }
}

void ball_window_collision_handler(RenderWindow& a_window, Ball& a_ball)
{
    FloatRect ballBounds = a_ball.getGlobalBounds();
    auto windowSize = a_window.getSize();
    float buffer = 10.0f;

    if (ballBounds.left <= buffer || ballBounds.left + ballBounds.width >= windowSize.x - buffer)
    {
        a_ball.elastic_horizontal();
    }

    if (ballBounds.top <= buffer || ballBounds.top + ballBounds.height >= windowSize.y - buffer)
    {
        a_ball.elastic_vertical();
    }
}

void ball_paddle_collision_handler(Ball& a_ball, Paddle& a_paddle)
{
    auto ballBounds = a_ball.getGlobalBounds();
    auto paddleBounds = a_paddle.getGlobalBounds();
    if (check_collision(a_ball, a_paddle))
    {
        float overlapX = std::min(ballBounds.left + ballBounds.width, paddleBounds.left + paddleBounds.width) - std::max(ballBounds.left, paddleBounds.left);                
        float overlapY = std::min(ballBounds.top + ballBounds.height, paddleBounds.top + paddleBounds.height) -  std::max(ballBounds.top, paddleBounds.top); 

        if (overlapX < overlapY)
        {
            if (ballBounds.left < paddleBounds.left)
            {
                a_ball.move(-overlapX - 0.1f, 0);
            }
            else
            {
                a_ball.move(overlapX + 0.1f, 0); 
            }
            a_ball.elastic_horizontal();
        }
        else
        {
            if (ballBounds.top < paddleBounds.top)
            {
                a_ball.move(0, -overlapY - 0.1f); 
            }
            else
            {
                a_ball.move(0, overlapY + 0.1f); 
            }
            a_ball.elastic_vertical();
        }
    }
}

void ball_paddle_collision_handler(Paddle& a_paddle, Ball& a_ball)
{
    auto ballBounds = a_ball.getGlobalBounds();
    auto paddleBounds = a_paddle.getGlobalBounds();
    if (check_collision(a_ball, a_paddle))
    {
        float overlapX = std::min(ballBounds.left + ballBounds.width, paddleBounds.left + paddleBounds.width) - std::max(ballBounds.left, paddleBounds.left);                
        float overlapY = std::min(ballBounds.top + ballBounds.height, paddleBounds.top + paddleBounds.height) -  std::max(ballBounds.top, paddleBounds.top); 

        if (overlapX < overlapY)
        {
            if (ballBounds.left < paddleBounds.left)
            {
                a_ball.move(-overlapX - 0.1f, 0);
            }
            else
            {
                a_ball.move(overlapX + 0.1f, 0); 
            }
            a_ball.elastic_horizontal();
        }
        else
        {
            if (ballBounds.top < paddleBounds.top)
            {
                a_ball.move(0, -overlapY - 0.1f); 
            }
            else
            {
                a_ball.move(0, overlapY + 0.1f); 
            }
            a_ball.elastic_vertical();
        }
    }
}

bool ball_kill_zone_collision_handler(Ball& a_ball, RectangleShape& a_kill_zone)
{
    auto ballBounds = a_ball.getGlobalBounds();
    auto killBounds = a_kill_zone.getGlobalBounds();

    if(ballBounds.intersects(killBounds))
    {
        a_ball.vanish();
        return true;
    }
    return false;
}

}//namespace arkanoid