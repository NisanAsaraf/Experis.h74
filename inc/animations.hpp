#ifndef ANIME_H
#define ANIME_H
#include <SFML/Graphics.hpp>
#include "leaderboard.hpp"
#include <string>
#include "scenes.hpp"
#include "ball.hpp"
#include "paddle.hpp"


namespace arkanoid
{

class Illustrator
{
public:
    void draw_BG_title(Title_Screen&, RenderWindow&);
    void draw_BG_level(Level_One&, RenderWindow&);
    void draw_BG_scoreboard(Score_Board&, RenderWindow&);

    void draw_title_screen(Title_Screen&, RenderWindow&);
    void draw_level_one(Level_One&, RenderWindow&);
    void draw_scoreboard(Score_Board&, RenderWindow&);

    void draw_win_screen(RenderWindow&);
    void draw_game_over_screen(RenderWindow&);
};

class Animator
{
public:
    void animate_ball(Ball&);
    void animate_paddle_right(Paddle&, Clock&);
    void animate_paddle_left(Paddle&, Clock&);
    void animate_paddle_stop(Paddle&);
};

}//namespace arkanoid
#include "inl/animations.hxx"

#endif//ANIME_H