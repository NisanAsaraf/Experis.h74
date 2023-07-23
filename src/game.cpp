#include "game.hpp"

namespace arkanoid
{

Arkanoid_Game::Arkanoid_Game()
{
    m_window_ptr = std::make_unique<Game_Window>();
    player = std::make_unique<Player>();
    make_title_screen();
}

void Arkanoid_Game::reset()
{
    m_window_ptr->restart(*scene);
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

void Arkanoid_Game::draw_title_screen()
{
    m_window_ptr->draw_title_screen(*scene);
}

void Arkanoid_Game::draw_level_one()
{
    m_window_ptr->draw_level_one(*player, *scene);
}

void Arkanoid_Game::draw_scoreBoard_screen()
{
    m_window_ptr->draw_scoreboard(*scene);
}

void Arkanoid_Game::run()
{
    while (m_window_ptr->isOpen())
    {   
        processEvents();
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                m_window_ptr->run_title_screen(*player, *scene, currentGameState);
                break;
            case GameState::Level1:
                m_window_ptr->run_level_one(*player, *scene, currentGameState);
                check_win_condition();
                break;
            case GameState::ScoreBoard:
                m_window_ptr->run_scoreboard_screen(*player, *scene, currentGameState);
                break;
            case GameState::Paused:
                break;
        }
    }
}

void Arkanoid_Game::processEvents()
{
    Event event;
    RenderWindow& window = m_window_ptr->getWindow();

    while (window.pollEvent(event))
    {   
        m_window_ptr->close_window_check(event);
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                if(m_window_ptr->title_screen_button_click_handler(*scene, event))
                {
                    make_level_one();
                }
                break;
            case GameState::Level1:
                m_window_ptr->paddle_movement_control(*scene, event, currentGameState);
                break;
            case GameState::ScoreBoard:
                new_high_score_check();
                m_window_ptr->pressed_any_key(event);
                
                break;
            case GameState::Paused:
                break;
        }
    }
}

bool Arkanoid_Game::new_high_score_check()
{
    uint32_t score = static_cast<uint32_t>(player->get_score());
    uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

    PlayerData new_player{"", score, elapsedTimeMs};
    ScoresFileManager score_manager;

    if(score_manager.check_new_high_score(new_player))
    {
        player->set_name(m_window_ptr->input_name());
        update_top_scores();
        return true;
    }
    return false;
}

void Arkanoid_Game::check_win_condition()
{
    if((*player).get_score() == WIN_SCORE)
    {
        m_window_ptr->game_win_screen();
        make_scoreBoard_screen();
    }
}

void Arkanoid_Game::update_top_scores()
{
    ScoresFileManager sc_manager;

    std::string playerName = player->get_name();
    std::array<char, 32> nameArray{};
    size_t nameLength = std::min(playerName.size(), nameArray.size() - 1);
    std::copy_n(playerName.c_str(), nameLength, nameArray.begin());
    nameArray[nameLength] = '\0';

    uint32_t score = static_cast<uint32_t>(player->get_score());
    uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

    std::unique_ptr<PlayerData> playerData = std::make_unique<PlayerData>();
    std::memcpy((*playerData).name, nameArray.data(), nameArray.size());

    (*playerData).score = score;
    (*playerData).elapsedTimeMs = elapsedTimeMs;
    sc_manager.update_top10_file(*playerData);
}


}//namepspace arkanoid
