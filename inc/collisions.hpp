#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
namespace arkanoid
{
using namespace sf;

bool check_collision(sf::Shape& ,sf::Shape& );
bool check_collision(sf::Shape&, sf::RenderWindow&);
void ball_block_collision_handler(sf::RectangleShape& , sf::CircleShape&);

}//namespace arkanoid
#endif