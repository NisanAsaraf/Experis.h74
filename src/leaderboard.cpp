#include "../inc/leaderboard.hpp"

namespace arkanoid
{

void ScoresFileManager::update_top10_file(PlayerData a_player)
{
    std::vector<PlayerData> top_10;
    load_scores(top_10);
    top_10.push_back(a_player);
    scoreboard_recalculation(top_10);
    save_scores(top_10);
}

void ScoresFileManager::load_scores(std::vector<PlayerData>& a_top_10)
{
    std::ifstream inputFile("../../assets/scoreboard/top_scores.dat", std::ios::binary);
    if (inputFile.is_open())
    {
        a_top_10.clear();
        while (true)
        {
            std::unique_ptr<PlayerData> playerPtr = std::make_unique<PlayerData>();
            PlayerData& player = *playerPtr;

            if (!inputFile.read(reinterpret_cast<char*>(&player.score), sizeof(player.score)))
            {
                break;
            }
            if (!inputFile.read(reinterpret_cast<char*>(&player.elapsedTimeMs), sizeof(player.elapsedTimeMs)))
            {
                break;
            }

            inputFile.read(player.name, sizeof(player.name));
            player.name[sizeof(player.name) - 1] = '\0'; 

            a_top_10.push_back(std::move(player)); 
        }
        inputFile.close();
    }
    else
    {
        create_scores_file();
    }
}

void ScoresFileManager::save_scores(std::vector<PlayerData>& a_top_10)
{
    std::ofstream outputFile("../../assets/scoreboard/top_scores.dat", std::ios::binary);
    if (outputFile.is_open())
    {
        for (const PlayerData& player : a_top_10)
        {
            outputFile.write(reinterpret_cast<const char*>(&player.score), sizeof(player.score));
            outputFile.write(reinterpret_cast<const char*>(&player.elapsedTimeMs), sizeof(player.elapsedTimeMs));
            outputFile.write(player.name, sizeof(player.name));
        }
        outputFile.close();
    }
    else
    {
        throw std::runtime_error("Error_Save: Unable to open file for reading.");
    }
}

void ScoresFileManager::scoreboard_recalculation(std::vector<PlayerData>& a_top_10)
{   
    std::sort(a_top_10.begin(), a_top_10.end(), [](PlayerData const& p1, PlayerData const& p2) 
    {
        if(p1.score > p2.score)
        {
            return true;
        } 
        else if(p1.score == p2.score)
        {
            return p1.elapsedTimeMs < p2.elapsedTimeMs;
        }
        return false;
    });

    if(a_top_10.size() > 10)
    {
        a_top_10.pop_back();
    }
}

bool ScoresFileManager::check_new_high_score(PlayerData const& new_player_data)
{
    std::vector<PlayerData> top_10;
    load_scores(top_10);
    
    if(top_10.empty())
    {
        return true;
    }

    for(auto& player_data : top_10)
    {
        if(player_data.score < new_player_data.score)
        {
            return true;
        }
        else if(player_data.score == new_player_data.score)
        {
            if(player_data.elapsedTimeMs > new_player_data.elapsedTimeMs)
            {
                return true;
            }
        }
    }
    return false;
}

void ScoresFileManager::create_scores_file()
{
    std::ofstream file("../..//assets/scoreboard/top_scores.dat");
}

}//namespace arkanoid