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

    void draw_BG_title(Title_Screen& titleScreen, sf::RenderWindow& window);
    void draw_BG_level(Level_One& levelOne, sf::RenderWindow& window);
    void draw_BG_scoreboard(Score_Board& scoreboard, sf::RenderWindow& window);

    void draw_title_screen(Title_Screen& titleScreen, sf::RenderWindow& window);
    void draw_level_one(Level_One& levelOne, sf::RenderWindow& window);
    void draw_scoreboard(Score_Board& scoreboard, sf::RenderWindow& window);
    void draw_win_screen(sf::RenderWindow& window);
    void draw_game_over_screen(sf::RenderWindow& window);
    void draw_pause(sf::RenderWindow& window);

    void draw_score(size_t score, sf::RenderWindow& window);
    void draw_life_bar(size_t lives, sf::RenderWindow& window);

    std::string draw_input_name_screen(sf::RenderWindow& window);

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