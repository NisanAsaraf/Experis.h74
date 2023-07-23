#include "game.hpp"

namespace arkanoid
{

Arkanoid_Game::Arkanoid_Game()
{
    player = std::make_unique<Player>();
    m_window_ptr = std::make_unique<Game_Window>();
}

void Arkanoid_Game::run()
{
    m_window_ptr->run();
}

void Arkanoid_Game::reset()
{
    m_window_ptr->restart();
}

void Arkanoid_Game::make_title_screen()
{
    currentGameState = GameState::TitleScreen;
    scene = std::make_unique<Title_Screen>();
    Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
    title_scrn->create();
    high_score_entered = false;
}

void Arkanoid_Game::make_level_one()
{
    currentGameState = GameState::Level1;
    clock.restart();

    scene = std::make_unique<Level_One>();
    Level_One* level_one = dynamic_cast<Level_One*>(scene.get());
    level_one->create();
}

void Arkanoid_Game::make_scoreBoard_screen()
{
    currentGameState = GameState::ScoreBoard;

    std::vector<PlayerData> top_players;
    ScoresFileManager sc_manager;
    sc_manager.load_scores(top_players);

    scene = std::make_unique<Score_Board>(top_players);
    Score_Board* score_scrn = dynamic_cast<Score_Board*>(scene.get());
    score_scrn->create();
}

}//namepspace arkanoid
