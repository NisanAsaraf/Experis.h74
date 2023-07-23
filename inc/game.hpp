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
    std::unique_ptr<RenderWindow> m_window_ptr;
};  

}//namepspace arkanoid
#endif //GAME_H
