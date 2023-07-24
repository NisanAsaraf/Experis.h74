#include "abs_scene.hpp"
#include "UI.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"

namespace arkanoid
{
    using namespace sf;
/*  

    std::vector<std::unique_ptr<Button>>& get_buttons();
    std::vector<std::unique_ptr<Block>>& get_blocks();
    Paddle& get_paddle();

    std::unique_ptr<sf::Texture> const& get_BG();
    std::unique_ptr<sf::RectangleShape> const& get_kill_zone();
    std::unique_ptr<sf::RectangleShape> const& get_border();
    std::vector<std::unique_ptr<Ball>> const& get_balls();

    void make_blocks(); 
    void make_paddle();
    void make_kill_zone(sf::Vector2f a_size);
    void make_border(sf::Vector2f a_size);
    void spawn_ball();
    void paddle_reset();

    size_t get_win_score() const;
    size_t get_level_number() const;
 */


std::vector<std::unique_ptr<Button>> const& Scene::get_buttons() const
{
    return buttons;
}

std::vector<std::unique_ptr<Block>> const& Scene::get_blocks() const
{
    return blocks;
}

Paddle const& Scene::get_paddle() const
{
    return *paddle;
}

std::unique_ptr<Texture> const& Scene::get_BG() const
{
    return backgroundTexture;
}


std::unique_ptr<sf::RectangleShape> const& get_kill_zone()
{

}

std::unique_ptr<sf::RectangleShape> const& get_border()
{

}

std::vector<std::unique_ptr<Ball>> const& get_balls()
{

}

size_t Scene::get_win_score() const
{
    return 0;
}

size_t Scene::get_level_number() const
{
    return lvl;;
}



}//namespace arkanoid