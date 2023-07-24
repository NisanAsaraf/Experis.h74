#include "abs_scene.hpp"
#include "UI.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"

namespace arkanoid
{
using namespace sf;

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


std::unique_ptr<sf::RectangleShape> const& Scene::get_kill_zone() const
{
    return kill_zone;
}

std::unique_ptr<sf::RectangleShape> const& Scene::get_border() const
{
    return border;
}

std::vector<std::unique_ptr<Ball>> const& Scene::get_balls() const
{
    return balls;
}

size_t Scene::get_win_score() const
{
    return 0;
}

size_t Scene::get_level_number() const
{
    return lvl;;
}

void make_blocks(); //<<

void Scene::make_paddle()
{
    paddle = std::make_unique<Paddle>();
}

void Scene::make_kill_zone(Vector2f a_size)
{
    kill_zone = std::make_unique<RectangleShape>(a_size);
    kill_zone->setPosition(0, a_size.y - 10);
    kill_zone->setFillColor(Color::Transparent);
}

void Scene::make_border(Vector2f a_size)
{
    Color Teal(0, 128, 128);
    border = std::make_unique<sf::RectangleShape>(a_size - Vector2f(10.0f,10.0f));

    border->setFillColor(Color::Transparent);
    border->setPosition(5.0f, 5.0f);
    border->setOutlineThickness(5.0f);
    border->setOutlineColor(Teal);
}

void Scene::spawn_ball()
{
    balls.emplace_back(std::make_unique<Ball>());
}

void Scene::paddle_reset()
{
    paddle->reset();
}

}//namespace arkanoid