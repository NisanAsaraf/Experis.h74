#include "../inc/collisions.hpp"
#include <SFML/Graphics.hpp>

namespace arkanoid
{
    
void ball_block_collision_handler(Collidable& a_shape_1, Collidable& a_shape_2)
{
    if(check_collision(a_shape_1, a_shape_2)) //better to not delete from the vector so to not handle all the memory problems...
    {
        a_shape_1.Collision();
        a_shape_2.Collision();
    }
}

bool check_collision(Collidable& a_shape_1, Collidable& a_shape_2)
{
    FloatRect bounds1 = a_shape_1.getGlobalBounds();
    FloatRect bounds2 = a_shape_2.getGlobalBounds();

    return (bounds1.intersects(bounds2));
}

bool check_window_collision(Collidable& a_shape, RenderWindow& a_window , float a_buffer)
{
    FloatRect shape_bounds = a_shape.getGlobalBounds();
    FloatRect window_bounds(Vector2f(a_buffer, a_buffer), Vector2f(a_window.getSize().x - a_buffer, a_window.getSize().y - a_buffer));

    return (shape_bounds.intersects(window_bounds));
}

}//namespace arkanoid