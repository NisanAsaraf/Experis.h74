#ifndef ABS_SCENE_H
#define ABS_SCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "button.hpp"
#include "paddle.hpp"
#include "block.hpp"
#include "ball.hpp"
#include "leaderboard.hpp"
#include "life.hpp"

namespace arkanoid
{
    
class Scene
{
public:
    Scene() = default;
    virtual void create() = 0;
    virtual void reset() = 0;
    virtual size_t get_level_number() const;

    std::vector<std::unique_ptr<Button>> const& get_buttons() const;
    std::vector<std::unique_ptr<Block>> const& get_blocks() const;
    Paddle& get_paddle() const;
    bool check_all_blocks_gone();

    std::unique_ptr<sf::Texture> const& get_BG() const;
    std::unique_ptr<sf::RectangleShape> const& get_kill_zone() const;
    std::unique_ptr<sf::RectangleShape> const& get_border() const;
    std::vector<std::unique_ptr<Ball>> const& get_balls() const;
    void load_blocks_from_json(std::ifstream& file);
    std::vector<sf::Text> const& getTexts();
    sf::Text& getHeader();

protected:
    void make_paddle();
    void make_kill_zone(sf::Vector2f a_size);
    void make_border(sf::Vector2f a_size);
    void spawn_ball();
    void paddle_reset();

protected:
    std::unique_ptr<sf::Texture> backgroundTexture;
    std::vector<std::unique_ptr<Button>> buttons;

    std::unique_ptr<sf::RectangleShape> border;
    std::unique_ptr<sf::RectangleShape> kill_zone;

    std::vector<std::unique_ptr<Block>> blocks;
    std::unique_ptr<Paddle> paddle;
    std::vector<std::unique_ptr<Ball>> balls;

    std::vector<PlayerData> m_players;
    sf::Text m_header;
    std::vector<sf::Text> m_texts;
    size_t lvl;
};

}//namespace arkanoid

#endif