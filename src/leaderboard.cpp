#include "../inc/leaderboard.hpp"
namespace arkanoid
{
    void ScoresFileManager::top_10_handler(PlayerData const& a_player)
    {
        std::vector<PlayerData> top_10;
    
        load_scores(top_10);
        top_10.push_back(a_player);

        scoreboard_recalculation(top_10);
        save_scores(top_10);
    }

    void ScoresFileManager::load_scores(std::vector<PlayerData>& a_top_10)
    {
        std::ifstream file("/home/nisan/Experis.h74/assets/scoreboard/top_scores.txt");
        if (file.is_open())
            {
                std::string line;
                while (std::getline(file, line) && a_top_10.size() < 10)
                {
                    std::istringstream iss(line);
                    PlayerData player;
                    if (iss >> player.name >> player.score)
                    {
                        float elapsedTimeSeconds;
                        if (iss >> elapsedTimeSeconds)
                        {
                            player.elapsedTime = sf::seconds(elapsedTimeSeconds);
                            a_top_10.push_back(player);
                        }
                    }
                }
                file.close();
            }
            else
            {
                throw std::runtime_error("Error: Unable to load file for reading.");
            }
    }

    void ScoresFileManager::save_scores(std::vector<PlayerData>& a_top_10)
    {
        std::ofstream outputFile("/home/nisan/Experis.h74/assets/scoreBoard/top_scores.txt");
        if (outputFile.is_open())
        {
            for (const PlayerData& player : a_top_10)
            {
                outputFile << player.name << " " << player.score << " " << player.elapsedTime.asSeconds();
            }
            outputFile.close();
        }
        else
        {
            throw std::runtime_error("Error: Unable to open file for reading.");
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
                return p1.elapsedTime < p2.elapsedTime;
            }
            return false;
        });
        a_top_10.pop_back();
    }

}//namespace arkanoid