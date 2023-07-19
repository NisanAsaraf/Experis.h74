#include "../inc/collisions.hpp"

bool check_collision(sf::Shape& a_shape1,sf::Shape& a_shape2)
{
    sf::FloatRect shape1_bounds = a_shape1.getGlobalBounds();
    sf::FloatRect shape2_bounds = a_shape2.getGlobalBounds();

    return (shape1_bounds.intersects(shape2_bounds));
}
