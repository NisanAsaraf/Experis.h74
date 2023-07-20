#include "../inc/player.hpp"

namespace arkanoid
{

Player::Player()
:m_name{}
,m_score{0}
,m_lives{3}
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

void Player::reset()
{
    m_score = 0;
    m_lives = 3;
}

size_t const& Player::get_score()
{
    return m_score;
}

void Player::hit()
{
    m_lives--;
}

bool Player::is_dead()
{
    return !m_lives;
}

}//namepsace arkanoid
