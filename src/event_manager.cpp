#include "event_manager.hpp"

namespace arkanoid
{
using namespace sf;

bool Event_Manager::title_screen_button_event_handler(Scene& a_scene, sf::Event& event)
{

}

void Event_Manager::paddle_movement_control(Scene& a_scene, sf::Event const&, GameState& currentGameState){

}

bool Event_Manager::close_window_check(sf::Event const& event)
{
    if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
    {
        return true;
    }
    return false;
}

bool Event_Manager::pressed_any_key(sf::Event const& event)
{
    if ((event.type == Event::KeyPressed && event.key.code != Keyboard::Escape))
    {
        return true;
    }
    return false;
}

}//arkanoid
