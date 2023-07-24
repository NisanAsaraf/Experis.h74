#ifndef GAME_H
#define GAME_H
#include "window.hpp"
#include "config.hpp"

namespace arkanoid
{
class Arkanoid_Game
{
public:
    Arkanoid_Game();
    void run();
    void reset();
private:
    void draw_title_screen();
    void draw_level_one();
    void draw_scoreBoard_screen();

    void make_title_screen();
    void make_level_one();
    void make_level_two();
    void make_scoreBoard_screen();

    void advance_level();

    void check_win_condition();
    void processEvents();
    bool new_high_score_check();
    void update_top_scores();
private:

    std::unique_ptr<Game_Window> m_window_ptr;
    std::unique_ptr<Player> player;
    std::unique_ptr<Scene> scene;
    
    sf::Clock clock;
    GameState currentGameState;

    bool is_high_score_already_entered;

};  

}//namepspace arkanoid
#endif //GAME_H

