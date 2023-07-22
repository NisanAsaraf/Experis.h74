#ifndef LEADRBRD_H
#define LEADRBRD_H
#include "player.hpp"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <algorithm>

namespace arkanoid
{

struct PlayerData
{
    std::string name;
    size_t score;
    sf::Time elapsedTime;
};

class ScoresFileManager
{
public:
    void update_top10_file(PlayerData const& a_player);
    void load_scores(std::vector<PlayerData>& a_top_10);
    bool check_new_high_score(PlayerData const&);
private:
    void save_scores(std::vector<PlayerData>& a_top_10);
    void scoreboard_recalculation(std::vector<PlayerData>& a_top_10);
};

}//namespace arkanoid
#endif