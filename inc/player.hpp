#ifndef PLAYER_H
#define PLAYER_H
#include <string>

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
    std::string const& get_name();
    void set_name(std::string a_name);
    size_t const& get_score();
    void update_score();
private:
    std::string m_name;
    size_t m_score;
    size_t m_total_score;
    size_t m_lives;
};

}//namepsace arkanoid

#endif