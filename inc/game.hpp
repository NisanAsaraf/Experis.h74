#ifndef GAME_H
#define GAME_H
#include "window.hpp"

namespace arkanoid
{

enum class GameState
{
    TitleScreen,
    Level1,
    ScoreBoard,
    Paused,
};

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
    void make_scoreBoard_screen();
    void check_win_condition();
    void processEvents();
private:
    std::unique_ptr<Game_Window> m_window_ptr;
    std::unique_ptr<Player> player;
    std::unique_ptr<Scene> scene;
    
    Clock clock;
    GameState currentGameState;

    bool high_score;
    bool high_score_entered;
};  

}//namepspace arkanoid
#endif //GAME_H

