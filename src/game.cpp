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
    sound_manager.set_scene_music("title_screen.ogg");
    sound_manager.play_scene_music();
}

void Arkanoid_Game::make_level_one()
{
    currentGameState = GameState::Level;
    player->reset_to_next_level();
    clock.restart();
    scene = std::make_unique<Level_One>();
    scene ->create();
    sound_manager.set_scene_music("level_one.ogg");
    sound_manager.play_scene_music();
}

void Arkanoid_Game::make_level_two()
{
    currentGameState = GameState::Level;
    clock.restart();
    player->reset_to_next_level();
    scene = std::make_unique<Level_Two>();
    scene ->create();
    sound_manager.set_scene_music("level_two.ogg");
    sound_manager.play_scene_music();
}

void Arkanoid_Game::make_level_three()
{
    currentGameState = GameState::Level;
    clock.restart();
    player->reset_to_next_level();
    scene = std::make_unique<Level_Three>();
    scene ->create();
    sound_manager.set_scene_music("level_three.ogg");
    sound_manager.play_scene_music();
}

void Arkanoid_Game::make_level_four()
{
    currentGameState = GameState::Level;
    clock.restart();
    player->reset_to_next_level();
    scene = std::make_unique<Level_Four>();
    scene ->create();
    sound_manager.set_scene_music("level_three.ogg");
    sound_manager.play_scene_music();
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

void Arkanoid_Game::draw_level()
{
    m_window_ptr->draw_level(*player, *scene);
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
        handleCollisions();
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                m_window_ptr->run_title_screen(*player, *scene, currentGameState);
                break;
            case GameState::Level:
                m_window_ptr->run_level(*player, *scene, currentGameState);
                check_win_condition();
                check_lose_condition();
                break;
            case GameState::ScoreBoard:
                m_window_ptr->run_scoreboard_screen(*player, *scene, currentGameState);
                break;
            case GameState::Paused:
                break;
        }
    }
}

void Arkanoid_Game::mute_sound_handler(Event& event)
{
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q)
    {
        ref_clock.restart();
        m_window_ptr->set_mute_status(sound_manager.mute_sound());
    }
}

void Arkanoid_Game::processEvents()
{
    Event event;
    sf::RenderWindow& window = m_window_ptr->getWindow();

    while (window.pollEvent(event))
    {   
        mute_sound_handler(event);
        if(m_window_ptr->close_window_check(event))
        {
            sound_manager.stop_scene_music();
        }
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                if(m_window_ptr->title_screen_button_event_handler(*scene, event))
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
    player->update_total_score();
    uint32_t score = static_cast<uint32_t>(player->get_total_score());
    uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

    PlayerData new_player{"", score, elapsedTimeMs};
    ScoresFileManager score_manager;

    if(!is_high_score_already_entered && score_manager.check_new_high_score(new_player))
    {
        std::string a_name;

        if(!m_window_ptr->input_name(a_name))
        {
            return false;
        }

        player->set_name(a_name);
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
    else if(scene->get_level_number() == 2)
    {
        make_level_three();
    }
    else if(scene->get_level_number() == 3)
    {
        make_level_four();
    }
    else if(scene->get_level_number() == 4)
    {
        make_scoreBoard_screen();
    }
}

void Arkanoid_Game::check_win_condition()
{
    if(scene->check_all_blocks_gone())
    {
        sound_manager.stop_scene_music();
        sound_manager.play_win_game_sound();
        m_window_ptr->game_win_screen();
        advance_level();
    }
}
void Arkanoid_Game::check_lose_condition()
{
    if(player->is_dead())
    {
        sound_manager.stop_scene_music();
        sound_manager.play_lose_game_sound();
        m_window_ptr->game_over_screen();
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

    uint32_t score = static_cast<uint32_t>(player->get_total_score());
    uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

    std::unique_ptr<PlayerData> playerData = std::make_unique<PlayerData>();
    std::memcpy((*playerData).name, nameArray.data(), nameArray.size());

    (*playerData).score = score;
    (*playerData).elapsedTimeMs = elapsedTimeMs;
    sc_manager.update_top10_file(*playerData);
}

void Arkanoid_Game::paddle_out_of_bounds_handler()
{
    Paddle& pad = scene->get_paddle();

    FloatRect paddleBounds = pad.getGlobalBounds();
    FloatRect borderBounds = (*scene->get_border()).getGlobalBounds();

    float newY = pad.getPosition().y;
    float newXL = borderBounds.left + 5.0f;
    float newXR = borderBounds.left + borderBounds.width - paddleBounds.width - 5.0f;

    if (paddleBounds.left < borderBounds.left)
    {
        pad.setPosition(newXL,newY);
    }
    else if (paddleBounds.left + paddleBounds.width > borderBounds.left + borderBounds.width)
    {
        pad.setPosition(newXR,newY);
    }
}

void Arkanoid_Game::slow_down_game()
{
    auto& balls = scene->get_balls();
    for (auto& ballPtr : balls)
    {
        ballPtr->ball_slow_down();
    }
}

void Arkanoid_Game::random_gift_handler()
{
    RandomNumberGenerator generator;
    int gift_number = generator.getRandomNumber();

    switch(gift_number)
    {
        case 0:
            scene->get_paddle().upgrade_size();
            break;
        case 1:
            player->add_life();
            break;
        case 2:
            player->add_score(1000);
            break;
        case 3:
            scene->get_paddle().upgrade_size();
            break;
        case 4:
            slow_down_game();
            ref_clock.restart();
            break;
    }
}

void Arkanoid_Game::level_collisions_handler()
{
    Paddle& pad = scene->get_paddle();
    auto& blocks = scene->get_blocks(); 
    auto& balls = scene->get_balls();

    paddle_out_of_bounds_handler();

    for (const auto& ballPtr : balls)
    {
        if(ballPtr->is_slow() && ref_clock.getElapsedTime().asSeconds() >= 5)
        {
            ballPtr->ball_return_normal_speed();
        }

        if(ballPtr->isVanished())
        {
            continue;
        }

        for (auto& block : blocks)
        {   
            if(block->isVanished())//slight optimization
            {
                continue;
            }
            if(collision_manager.check_collision(*ballPtr, *block))
            {   sound_manager.play_block_collision_sound();
                if(block->isExplode())
                {
                    sound_manager.play_explosion_sound();
                    for (auto& other_block : blocks)
                    {
                        if(other_block->isVanished() || block == other_block)//slight optimization
                        {
                            continue;
                        }
                        if (collision_manager.block_blocks_collision_handler(*block, *other_block))
                        {
                            if(other_block->isGift())
                            {
                                random_gift_handler();
                                sound_manager.play_gift_sound();
                            }
                            player->add_score(other_block->getScoreValue(scene->get_level_number()));
                        }
                    }
                    collision_manager.ball_block_collision_handler(*block, *ballPtr);
                }
                else if(block->isGift())
                {
                    sound_manager.play_gift_sound();
                    random_gift_handler();
                    collision_manager.ball_block_collision_handler(*block, *ballPtr);//will vanish a block
                }
                else
                {
                    player->add_score(block->getScoreValue(scene->get_level_number()));
                    collision_manager.ball_block_collision_handler(*block, *ballPtr);//will vanish a block
                }
                //a_scene.remove_block(block&); // problematic
            }
        }
        collision_manager.ball_window_collision_handler(*ballPtr, m_window_ptr->getWindow());
        collision_manager.ball_paddle_collision_handler(*ballPtr,pad);

        if(collision_manager.ball_kill_zone_collision_handler(*ballPtr, *scene->get_kill_zone()))  // will vanish a ball , wont delete it from the vector
        {
            player->hit();
            ballPtr->reset();
            pad.reset();
        }
    }
}

void Arkanoid_Game::handleCollisions()
{
    switch (currentGameState)
    {
        case GameState::TitleScreen:
            break;
        case GameState::Level:
            level_collisions_handler();
            break;
        case GameState::ScoreBoard:
            break;
        case GameState::Paused:
            break;
    }
}


}//namepspace arkanoid
