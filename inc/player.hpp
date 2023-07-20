#ifndef PLAYER_H
#define PLAYER_H
#include <string>

namespace arkanoid
{

class Player
{
public:
    Player();
    void add_score(size_t);
    void hit();
    void reset();
    bool is_dead();
    std::string const& get_name();
    size_t const& get_score();
private:
    std::string m_name;
    size_t m_score;
    size_t m_lives;
};

}//namepsace arkanoid

#endif