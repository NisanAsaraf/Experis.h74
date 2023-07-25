#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "config.hpp"

namespace arkanoid
{

class Player
{
public:
    Player();
    void add_score(size_t a_score);
    void hit();
    void reset_to_next_level();
    bool is_dead() const;
    size_t get_lives();
    std::string const& get_name() const;
    void set_name(std::string a_name);
    void update_total_score();
    size_t const& get_level_score() const;
    size_t const& get_total_score() const;
    void add_life();
private:
    std::string m_name;
    size_t m_score;
    size_t m_total_score;
    size_t m_lives;
};

}//namepsace arkanoid

#endif