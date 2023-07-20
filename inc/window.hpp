#include "../inc/paddle.hpp"
#include "../inc/levels.hpp"
#include "../inc/ball.hpp"
#include "../inc/block.hpp"
#include "../inc/collisions.hpp"
#include "../inc/animations.hpp"
#include "../inc/player.hpp"
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

    void create_player();
    void make_paddle();
    void make_border();
    void make_kill_zone();
    void spawn_ball();
    void paddle_reset();
    void paddle_movement_control(Event const&);
    void close_window_check(Event const&);
    void win_condition();
    void run();
    void restart();
    void game_over_screen();
    void game_win_screen();
    void draw_scoreboard();
    void make_level_one();
    void animate_balls();
    void animate_paddle_right();
    void animate_paddle_left();
    void animate_paddle_stop();
    void draw_shapes();
    void draw_level();
    void processEvents();
    void paddle_out_of_bounds_handler();
    void handleCollisions();

private:
    RenderWindow window;
    Clock clock;
    std::unique_ptr<RectangleShape> border;
    std::unique_ptr<RectangleShape> kill_zone;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Player> player;
    std::unique_ptr<Level_One> level;
    Font font;
};

} // namespace arkanoid
