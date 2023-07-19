#include "../inc/collisions.hpp"

bool check_collision(sf::Shape& a_shape1,sf::Shape& a_shape2)
{
    sf::FloatRect shape1_bounds = a_shape1.getGlobalBounds();
    sf::FloatRect shape2_bounds = a_shape2.getGlobalBounds();

    return (shape1_bounds.intersects(shape2_bounds));
}

bool check_collision(sf::Shape& a_shape, sf::RenderWindow& a_window , float a_buffer)
{
    sf::FloatRect shape_bounds = a_shape.getGlobalBounds();
    sf::FloatRect window_bounds(sf::Vector2f(a_buffer, a_buffer), sf::Vector2f(a_window.getSize().x - a_buffer, a_window.getSize().y - a_buffer));

    return (shape_bounds.intersects(window_bounds));
}