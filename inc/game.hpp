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
    GameState currentGameState;
    bool high_score;
    bool high_score_entered;
};  

}//namepspace arkanoid
#endif //GAME_H
