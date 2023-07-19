#ifndef COLLISIONS_H
#define COLLISIONS_H

namespace arkanoid
{
using namespace sf;

class Collidable 
{
public:
    virtual ~Collidable() = default;
    virtual FloatRect getGlobalBounds() = 0;
    virtual void Collision() = 0;
};

bool check_collision(Collidable&, Collidable&);

void ball_block_collision_handler(Collidable&, Collidable& );

}//namespace arkanoid
#endif