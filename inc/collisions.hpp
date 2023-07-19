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

bool check_window_collision(Shape&, RenderWindow&, float);

void ball_block_collision_handler(Ball&, Block&);

void ball_block_collision_handler(Block&, Ball&);

void ball_window_collision_handler(Ball&, RenderWindow&);

void ball_window_collision_handler(RenderWindow&, Ball&);

void ball_paddle_collision_handler(Ball&, Paddle&);

void ball_paddle_collision_handler(Paddle&, Ball&);

bool ball_kill_zone_collision_handler(Ball&, RectangleShape&);

}//namespace arkanoid
#endif