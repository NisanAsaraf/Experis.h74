#include "abs_scene.hpp"

namespace arkanoid
{
using json = nlohmann::json;
using namespace sf;

std::vector<std::unique_ptr<Button>> const& Scene::get_buttons() const
{
    return buttons;
}

std::vector<std::unique_ptr<Block>> const& Scene::get_blocks() const
{
    return blocks;
}

Paddle& Scene::get_paddle() const
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

bool Scene::check_all_blocks_gone()
{
    for(auto& block : blocks)
    {
        if(!block->isVanished())
        {
            return false;
        }
    }
    return true;
}

void Scene::spawn_ball()
{
    balls.emplace_back(std::make_unique<Ball>());
}

void Scene::paddle_reset()
{
    paddle->reset();
}

std::vector<sf::Text> const& Scene::getTexts()
{
    return m_texts;
}

sf::Text& Scene::getHeader()
{
    return m_header;
}


void Scene::load_blocks_from_json(std::ifstream& file)
{
    json level_data;
    file >> level_data;

    blocks.clear();

    for (const auto& block_data : level_data["blocks"])
    {
        int x = block_data["x"];
        int y = block_data["y"];
        std::string block_type = block_data["type"];

        std::unique_ptr<Block> block;
        if (block_type == "WhiteBlock")
        block = std::make_unique<WhiteBlock>(x, y);
        else if (block_type == "TealBlock")
            block = std::make_unique<TealBlock>(x, y);
        else if (block_type == "BrownBlock")
            block = std::make_unique<BrownBlock>(x, y);
        else if (block_type == "OrangeBlock")
            block = std::make_unique<OrangeBlock>(x, y);
        else if (block_type == "GreenBlock")
            block = std::make_unique<GreenBlock>(x, y);
        else if (block_type == "PurpleBlock")
            block = std::make_unique<PurpleBlock>(x, y);
        else if (block_type == "BlueBlock")
            block = std::make_unique<BlueBlock>(x, y);
        else if (block_type == "GrayBlock")
            block = std::make_unique<GrayBlock>(x, y);
        else if (block_type == "RedBlock")
            block = std::make_unique<RedBlock>(x, y);
        else if (block_type == "YellowBlock")
            block = std::make_unique<YellowBlock>(x, y);
        else if (block_type == "Breakable_Block")
            block = std::make_unique<Breakable_Block>(x, y);
        else if (block_type == "Explodable_Block")
            block = std::make_unique<Explodable_Block>(x, y);
        else if (block_type == "Gift_Block")
            block = std::make_unique<Gift_Block>(x, y);
        blocks.emplace_back(std::move(block));
    }
}

}//namespace arkanoid