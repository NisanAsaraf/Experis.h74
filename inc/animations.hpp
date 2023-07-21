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
    void draw_scoreboard(Score_Board& ,RenderWindow&);
    void draw_BG_scoreboard(Score_Board& a_scoreBoard,RenderWindow& a_window);
};

}//namespace arkanoid
#include "inl/animations.hxx"

#endif//ANIME_H