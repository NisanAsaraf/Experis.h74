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

    void run();
    void run_title_screen();
    void run_level_one();
    void run_scoreboard_screen();
    void make_scoreBoard_screen();
    void title_screen_button_click_handler(Event& event);
    void draw_level_one();
    void draw_title_screen();
    void new_high_score_check();
    void draw_background_title_screen();
    void draw_background_level_one();
    void draw_background_score_board();
    void paddle_movement_control(Event const&);
    bool close_window_check(Event const&);
    void win_condition();
    std::string input_name();
    void pause_game();
    void draw_hearts(size_t lives);
    void restart();
    void draw_scoreboard();
    void draw_background();
    void level_one_collisions_handler();
    void game_over_screen();
    void game_win_screen();
    void draw_score(size_t score);
    void make_title_screen();
    void draw_pause_text();
    void make_level_one();   
    void update_top_scores();
    void animate_balls();
    void animate_paddle_right();
    void animate_paddle_left();
    void animate_paddle_stop();
    void draw_shapes();
    void draw_scene();
    void restart_game_handler(Event const&);
    void processEvents();
    void paddle_out_of_bounds_handler();
    void handleCollisions();
private:
    enum class GameState
    {
        TitleScreen,
        Level1,
        ScoreBoard,
        Paused,
    };
private:
    RenderWindow window;
    Clock clock;
    GameState currentGameState;
    std::unique_ptr<Illustrator> illustrator;
    std::unique_ptr<Animator> animator;
    std::unique_ptr<Scene> scene;

    bool high_score;
    bool high_score_entered;
};

} // namespace arkanoid
