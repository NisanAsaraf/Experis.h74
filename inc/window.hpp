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
#include "game.hpp"

namespace arkanoid
{
using namespace sf;

class Game_Window
{
public:
    Game_Window();
    ~Game_Window() = default;

    void run_title_screen(Player& a_player, Scene& a_scene);
    void run_level_one(Player& a_player, Scene& a_scene);
    void run_scoreboard_screen(Player& a_player,Scene& a_scene);
    void run(Player& a_player, Scene& a_scene, GameState& a_gameState);

    void draw_background_title_screen(Scene& m_scene);
    void draw_background_level_one(Scene& a_scene);
    void draw_background_score_board(Scene& a_scene);
    void draw_background(Scene& m_scene);

    void draw_level_one(Player& a_player, Scene& a_scene);
    void draw_title_screen(Scene& a_scene);
    void draw_scoreboard(Player& a_player, Scene& a_scene);
    void draw_scene(Player& a_player, Scene& a_scene);

    void new_high_score_check(Player& a_player);


    void win_condition(Player& a_player);
    std::string input_name();
    void pause_game();
    void draw_hearts(size_t lives);
    void restart(Scene& a_scene);
    
    void level_one_collisions_handler(Player& a_player, Scene& a_scene);
    void game_over_screen();
    void game_win_screen();
    void draw_score(size_t score);

    void draw_pause_text();
    void update_top_scores(Player& a_player);

    void animate_balls(Scene& a_scene);
    void animate_paddle_right(Scene& a_scene);
    void animate_paddle_left(Scene& a_scene);
    void animate_paddle_stop(Scene& a_scene);

    void draw_shapes();

    void title_screen_button_click_handler(Scene& a_scene, Event& event);
    void paddle_movement_control(Scene& a_scene, Event const&);
    bool close_window_check(Event const&);
    void restart_game_handler(Scene& a_scene, Event const&);
    void processEvents(Player& a_player, Scene& a_scene);
    void paddle_out_of_bounds_handler(Scene& a_scene);
    void handleCollisions(Player& a_player, Scene& a_scene);

private:
    RenderWindow window;
    Clock clock;
    GameState currentGameState;
    std::unique_ptr<Illustrator> illustrator;
    std::unique_ptr<Animator> animator;

    bool high_score;
    bool high_score_entered;
};

} // namespace arkanoid
