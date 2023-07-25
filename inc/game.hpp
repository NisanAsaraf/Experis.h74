#ifndef GAME_H
#define GAME_H
#include "window.hpp"
#include "config.hpp"
#include "sound_manager.hpp"

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
    void make_level_three();
    void make_scoreBoard_screen();

    void advance_level();

    void check_win_condition();
    void check_lose_condition();
    void processEvents();
    bool new_high_score_check();
    void update_top_scores();
    void mute_sound_handler(sf::Event& event);
private:

    std::unique_ptr<Game_Window> m_window_ptr;
    Sound_Manager sound_manager;
    std::unique_ptr<Player> player;
    std::unique_ptr<Scene> scene;
    sf::Clock clock;
    GameState currentGameState;
    bool is_high_score_already_entered;

};  

}//namepspace arkanoid
#endif //GAME_H

