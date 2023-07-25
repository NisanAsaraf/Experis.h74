#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include "paddle.hpp"
#include "block.hpp"
#include "ball.hpp"

namespace arkanoid
{

bool check_collision(Ball& a_ball, Block& a_block);

bool check_collision(Block& a_block, Ball& a_ball);

bool check_collision(Ball& a_ball, Paddle& a_paddle);

bool check_collision(Paddle& a_paddle, Ball& a_ball);

void ball_block_collision_handler(Ball& a_ball, Block& a_block);

void ball_block_collision_handler(Block& a_block, Ball& a_ball);

bool check_window_collision(sf::Shape& a_shape, sf::RenderWindow& a_window, float a_buffer);

void ball_block_collision_handler(Ball& a_ball, Block& a_block);

void ball_block_collision_handler(Block& a_block, Ball& a_ball);

void ball_window_collision_handler(Ball& a_ball, sf::RenderWindow& a_window);

void ball_window_collision_handler(sf::RenderWindow& a_window, Ball& a_ball);

void ball_paddle_collision_handler(Ball& a_ball, Paddle& a_paddle);

void ball_paddle_collision_handler(Paddle& a_paddle, Ball& a_ball);

bool ball_kill_zone_collision_handler(Ball& a_ball, sf::RectangleShape& a_zone);

}//namespace arkanoid
#endif