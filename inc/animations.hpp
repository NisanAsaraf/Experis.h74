#ifndef ANIME_H
#define ANIME_H
#include <SFML/Graphics.hpp>
#include "leaderboard.hpp"
#include "scenes.hpp"

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
};


}//namespace arkanoid
#include "inl/animations.hxx"

#endif//ANIME_H