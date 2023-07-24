#include "../inc/player.hpp"

namespace arkanoid
{

Player::Player()
:m_name{}
,m_score{0}
,m_total_score{0}
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

void Player::set_name(std::string a_name)
{
    m_name = a_name;
}

void Player::reset_to_next_level()
{
    m_total_score += m_score;
    m_score = 0;
    m_lives = 3;
}

void Player::update_score()
{
    m_total_score += m_score;
}

size_t const& Player::get_score()
{
    return m_total_score;
}

size_t Player::get_lives()
{
    return m_lives;
}

void Player::hit()
{
    m_lives--;
}

bool Player::is_dead() const
{
    return !m_lives;
}

}//namepsace arkanoid
