#include "game.hpp"

namespace arkanoid
{

Arkanoid_Game::Arkanoid_Game()
{
    m_window_ptr = std::make_unique<Game_Window>();
}

void Arkanoid_Game::run()
{
    m_window_ptr->run();
}

void Arkanoid_Game::reset()
{
    m_window_ptr->restart();
}

}//namepspace arkanoid
