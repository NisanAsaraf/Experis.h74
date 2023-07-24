#ifndef G_WINDOW_H
#define G_WINDOW_H

#include "paddle.hpp"
#include "scenes.hpp"
#include "ball.hpp"
#include "block.hpp"
#include "collisions.hpp"
#include "animations.hpp"
#include "player.hpp"
#include "leaderboard.hpp"
#include "config.hpp"
#include <vector>
#include <random>

namespace arkanoid
{

class Game_Window
{
public:
    Game_Window();
    ~Game_Window() = default;
    
    void run_title_screen(Player& a_player, Scene& a_scene, GameState& currentGameState);
    void run_level(Player& a_player, Scene& a_scene, GameState& currentGameState);
    void run_scoreboard_screen(Player& a_player,Scene& a_scene, GameState& currentGameState);
    
    void draw_background_title_screen(Scene& m_scene);
    void draw_background_level_one(Scene& a_scene);
    void draw_background_score_board(Scene& a_scene);
    void draw_background(Scene& m_scene, GameState& currentGameState);

    void draw_level_one(Player& a_player, Scene& a_scene);
    void draw_title_screen(Scene& a_scene);
    void draw_scoreboard(Scene& a_scene);
    void draw_scene(Player& a_player, Scene& a_scene, GameState& currentGameState);

    bool new_high_score_check(Player& a_player);

    bool input_name(std::string& a_name);
    void pause_game(GameState& currentGameState);
    void draw_hearts(size_t lives);
    void restart(Scene& a_scene);
    
    void level_collisions_handler(Player& a_player, Scene& a_scene);
    void game_over_screen();
    void game_win_screen();
    void draw_score(size_t score);

    void draw_pause_text();

    void animate_balls(Scene& a_scene);
    void animate_paddle_right(Scene& a_scene);
    void animate_paddle_left(Scene& a_scene);
    void animate_paddle_stop(Scene& a_scene);

    void draw_shapes();

    bool title_screen_button_click_handler(Scene& a_scene, sf::Event& event);
    void paddle_movement_control(Scene& a_scene, sf::Event const&, GameState& currentGameState);
    bool close_window_check(sf::Event const&);
    bool pressed_any_key(sf::Event const& event);
    void paddle_out_of_bounds_handler(Scene& a_scene);
    void handleCollisions(Player& a_player, Scene& a_scene, GameState& currentGameState);

    bool isOpen();
    sf::RenderWindow& getWindow();
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::unique_ptr<Illustrator> illustrator;
    std::unique_ptr<Animator> animator;

    bool high_score;
    bool high_score_entered;
};

} // namespace arkanoid
#endif//G_WINDOW_H