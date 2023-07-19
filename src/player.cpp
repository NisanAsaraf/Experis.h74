#include "../inc/player.hpp"

namespace arkanoid
{

Player::Player(std::string const& a_name)
:m_name(a_name)
,m_score{0}
{
}

void Player::add_score(size_t add)
{
    m_score += add;
}

std::string const& Player::get_name()
{
    return m_name;
}

size_t const& Player::get_score()
{
    return m_score;
}

}//namepsace arkanoid
