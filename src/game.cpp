#include "game.hpp"

using namespace sf;
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
    make_title_screen();
}

void Arkanoid_Game::make_title_screen()
{
    currentGameState = GameState::TitleScreen;
    scene = std::make_unique<Title_Screen>();
    scene ->create();
    is_high_score_already_entered = false;
}

void Arkanoid_Game::make_level_one()
{
    currentGameState = GameState::Level;
    clock.restart();
    scene = std::make_unique<Level_One>();
    scene ->create();
}

void Arkanoid_Game::make_level_two()
{
    currentGameState = GameState::Level;
    clock.restart();

    scene = std::make_unique<Level_Two>();
    scene ->create();
}

void Arkanoid_Game::make_scoreBoard_screen()
{
    currentGameState = GameState::ScoreBoard;

    std::vector<PlayerData> top_players;
    ScoresFileManager sc_manager;
    sc_manager.load_scores(top_players);

    scene = std::make_unique<Score_Board>(top_players);
    scene->create();
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
            case GameState::Level:
                m_window_ptr->run_level(*player, *scene, currentGameState);
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
    sf::RenderWindow& window = m_window_ptr->getWindow();

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
            case GameState::Level:
                m_window_ptr->paddle_movement_control(*scene, event, currentGameState);
                break;
            case GameState::ScoreBoard:
                new_high_score_check();
                if(m_window_ptr->pressed_any_key(event))
                {
                    reset();
                }
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

    if(!is_high_score_already_entered && score_manager.check_new_high_score(new_player))
    {
        player->set_name(m_window_ptr->input_name());
        update_top_scores();
        is_high_score_already_entered = true;
        make_scoreBoard_screen();
        return true;
    }
    return false;
}

void Arkanoid_Game::advance_level()
{
    if(scene->get_level_number() == 1)
    {
        make_level_two();
    }

    if(scene->get_level_number() == 2)
    {
        make_scoreBoard_screen();
    }
}

void Arkanoid_Game::check_win_condition()
{
    if((*player).get_score() == scene->get_win_score())
    {
        m_window_ptr->game_win_screen();
        advance_level();
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
