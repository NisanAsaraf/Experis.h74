#ifndef EVE_MAN_H
#define EVE_MAN_H
#include "scenes.hpp"

namespace arkanoid
{
class Event_Manager
{
    bool title_screen_button_event_handler(Scene& a_scene, sf::Event& event);
    void paddle_movement_control(Scene& a_scene, sf::Event const&, GameState& currentGameState);
    bool close_window_check(sf::Event const&);
    bool pressed_any_key(sf::Event const& event);
};

}//arkanoid


#endif // EVE_MAN_H