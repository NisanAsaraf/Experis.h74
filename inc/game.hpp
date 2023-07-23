#ifndef GAME_H
#define GAME_H
#include "window.hpp"

namespace arkanoid
{

class Arkanoid_Game
{
public:
    Arkanoid_Game();
    void run();
    void reset();
    
    void make_title_screen();
    void make_level_one();
    void make_scoreBoard_screen();
private:
    enum class GameState
    {
        TitleScreen,
        Level1,
        ScoreBoard,
        Paused,
    };
    
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

