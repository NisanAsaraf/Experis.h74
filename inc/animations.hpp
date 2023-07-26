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

    void draw_BG_title(Scene& titleScreen, sf::RenderWindow& window);
    void draw_BG_level(Scene& levelOne, sf::RenderWindow& window);
    void draw_BG_scoreboard(Scene& scoreboard, sf::RenderWindow& window);

    void draw_title_screen(Scene& titleScreen, sf::RenderWindow& window);
    void draw_level(Scene& a_level_one, sf::RenderWindow& a_window);
    void draw_scoreboard(Scene& scoreboard, sf::RenderWindow& window);

    void draw_win_screen(sf::RenderWindow& window);
    void draw_game_over_screen(sf::RenderWindow& window);
    void draw_pause(sf::RenderWindow& window);

    void draw_button_hover(Button& a_button, sf::RenderWindow& window);
    void draw_button(Button& a_button, sf::RenderWindow& a_window);
    void draw_score(size_t score, sf::RenderWindow& window);
    void draw_life_bar(size_t lives, sf::RenderWindow& window);

    bool draw_input_name_screen(std::string& a_string, sf::RenderWindow& a_window);

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