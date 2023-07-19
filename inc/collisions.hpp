#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "paddle.hpp"
#include "block.hpp"
#include "ball.hpp"

namespace arkanoid//TODO: tried an abstraction of a collidable class, problematic...  
{
using namespace sf;

bool check_collision(Ball&, Block&);

bool check_collision(Block&, Ball&);

bool check_collision(Ball&, Paddle&);

bool check_collision(Paddle&, Ball&);

void ball_block_collision_handler(Ball&, Block&);

void ball_block_collision_handler(Block&, Ball&);

bool check_window_collision(Shape& a_shape, RenderWindow& a_window , float a_buffer);

void ball_block_collision_handler(Ball& a_ball, Block& a_block);

void ball_block_collision_handler(Block& a_block, Ball& a_ball);
}//namespace arkanoid
#endif