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
    Illustrator();
    void draw_BG_title(Title_Screen&, sf::RenderWindow&);
    void draw_BG_level(Level_One&, sf::RenderWindow&);
    void draw_BG_scoreboard(Score_Board&, sf::RenderWindow&);

    void draw_title_screen(Title_Screen&, sf::RenderWindow&);
    void draw_level_one(Level_One&, sf::RenderWindow&);
    void draw_scoreboard(Score_Board&, sf::RenderWindow&);

    void draw_win_screen(sf::RenderWindow&);
    void draw_game_over_screen(sf::RenderWindow&);
    void draw_pause(sf::RenderWindow&);
    void draw_score(size_t a_score ,sf::RenderWindow& a_window);
    void draw_life_bar(size_t lives,sf::RenderWindow& a_window);

    std::string draw_input_name_screen(sf::RenderWindow& a_window);
private:
    sf::Font m_font;
};

class Animator
{
public:
    void animate_ball(Ball&);
    void animate_paddle_right(Paddle&, sf::Clock&);
    void animate_paddle_left(Paddle&, sf::Clock&);
    void animate_paddle_stop(Paddle&);
};

}//namespace arkanoid
#include "inl/animations.hxx"

#endif//ANIME_H