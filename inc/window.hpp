#include "../inc/paddle.hpp"
#include "../inc/levels.hpp"
#include "../inc/ball.hpp"
#include "../inc/block.hpp"
#include "../inc/collisions.hpp"
#include "../inc/animations.hpp"

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

    void make_paddle();
    void make_border();
    void spawn_ball();
    void run();
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
    sf::RenderWindow window;
    std::unique_ptr<RectangleShape> border;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Level_One> level;
};

} // namespace arkanoid
