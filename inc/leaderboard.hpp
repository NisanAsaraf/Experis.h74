#ifndef LEADRBRD_H
#define LEADRBRD_H
#include "player.hpp"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>

namespace arkanoid
{
struct PlayerData
{
    char name[32];
    uint32_t score;
    uint64_t elapsedTimeMs;
};

class ScoresFileManager
{
public:
    void update_top10_file(PlayerData a_player);
    void load_scores(std::vector<PlayerData>& a_top_10);
    bool check_new_high_score(PlayerData const&);
    void create_scores_file();
private:
    void save_scores(std::vector<PlayerData>& a_top_10);
    void scoreboard_recalculation(std::vector<PlayerData>& a_top_10);
};

}//namespace arkanoid
#endif