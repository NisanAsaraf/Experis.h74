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





}//namespace arkanoid