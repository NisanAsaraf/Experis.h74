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
using namespace sf;

class Game_Window
{
public:
    Game_Window();
    ~Game_Window() = default;

    void run();
    void run_title_screen();
    void run_level_one();
    void create_player();
    void make_paddle();
    void make_border();
    void make_kill_zone();
    void title_screen_button_click_handler(Event& event);
    void spawn_ball();
    void paddle_reset();
    void draw_level_one();
    void draw_title_screen();
    void paddle_movement_control(Event const&);
    bool close_window_check(Event const&);
    void win_condition();
    void pause_game();
    void restart();
    void level_one_collisions_handler();
    void game_over_screen();
    void game_win_screen();
    void draw_scoreboard();
    void make_title_screen();
    void draw_pause_text();
    void make_level_one();   
    void top_10_handler();
    void animate_balls();
    void animate_paddle_right();
    void animate_paddle_left();
    void animate_paddle_stop();
    void draw_shapes();
    void draw_scene();
    void processEvents();
    void paddle_out_of_bounds_handler();
    void handleCollisions();
private:
    enum class GameState
    {
        TitleScreen,
        Level1,
    };
private:
    RenderWindow window;
    GameState currentGameState;
    Clock clock;
    std::unique_ptr<RectangleShape> border;
    std::unique_ptr<RectangleShape> kill_zone;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Player> player;
    std::unique_ptr<Scene> scene;
    Font font;
    bool paused;
};

} // namespace arkanoid
