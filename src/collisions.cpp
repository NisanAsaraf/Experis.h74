#include "../inc/collisions.hpp"
#include "../inc/block.hpp"
#include "../inc/ball.hpp"

namespace arkanoid
{

bool check_collision(Ball& a_ball, Block& a_block)
{
    FloatRect ball_bounds = a_ball.getGlobalBounds();
    FloatRect block_bounds = a_block.getGlobalBounds();

    return (ball_bounds.intersects(block_bounds));
}

bool check_collision(Shape& a_shape1,Shape& a_shape2)
{
    FloatRect shape1_bounds = a_shape1.getGlobalBounds();
    FloatRect shape2_bounds = a_shape2.getGlobalBounds();

    return (shape1_bounds.intersects(shape2_bounds));
}

bool check_collision(Shape& a_shape, RenderWindow& a_window , float a_buffer)
{
    FloatRect shape_bounds = a_shape.getGlobalBounds();
    FloatRect window_bounds(Vector2f(a_buffer, a_buffer), Vector2f(a_window.getSize().x - a_buffer, a_window.getSize().y - a_buffer));

    return (shape_bounds.intersects(window_bounds));
}

void ball_block_collision_handler(Block& a_block, Ball& a_ball)
{
    if(check_collision(a_ball, a_block)) //better to not delete from the vector so to not handle all the memory problems...
    {
        a_block.vanish();
    }
}

}