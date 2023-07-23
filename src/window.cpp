#include "../inc/window.hpp"
#include <exception>
#include <memory>
#include <fstream>
namespace arkanoid
{
using namespace sf;

    Game_Window::Game_Window()
    : window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
    ,"Arkanoid",Style::Titlebar | Style::Close)
    ,currentGameState(GameState::TitleScreen)
    ,high_score(false)
    ,high_score_entered(false)
    { 
        illustrator = std::make_unique<Illustrator>();
        animator = std::make_unique<Animator>();

        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        //make_title_screen();
        //make_level_one()
        //make_scoreBoard_screen();
    }

    void Game_Window::draw_background_title_screen(Scene& m_scene)
    {
        Title_Screen* title_screen_ptr = dynamic_cast<Title_Screen*>(&m_scene);
        illustrator->draw_BG_title(*title_screen_ptr,window);
    }

    void Game_Window::draw_background_level_one(Scene& m_scene)
    {
        Level_One* level_1 = dynamic_cast<Level_One*>(&m_scene);
        illustrator->draw_BG_level(*level_1,window);
    }

    void Game_Window::Game_Window::draw_background_score_board(Scene& m_scene)
    {
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(&m_scene);
        Illustrator illustrator;
        illustrator.draw_BG_scoreboard(*score_scrn,window);
    }
    
    void Game_Window::draw_background(Scene& m_scene)
    {
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                draw_background_title_screen(m_scene);
                break;

            case GameState::Level1:
                draw_background_level_one(m_scene);
                break;

            case GameState::ScoreBoard:
                draw_background_score_board(m_scene);
                break;

            case GameState::Paused:
                break;
        }   
    }

    void Game_Window::draw_hearts(size_t lives)
    {
        illustrator->draw_life_bar(lives, window);
    }

    void Game_Window::draw_score(size_t score)
    {
        illustrator->draw_score(score , window);
    }

    void Game_Window::draw_pause_text()
    {
        illustrator->draw_pause(window);
    }

    void Game_Window::draw_title_screen(Scene& a_scene)
    {
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(&a_scene);
        illustrator->draw_title_screen(*title_scrn, window);
    }

    void Game_Window::draw_level_one(Player& a_player, Scene& a_scene)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        illustrator->draw_level_one(*level_one, window);
        draw_hearts(a_player.get_lives());
    }

    void Game_Window::draw_scoreboard(Player& a_player, Scene& a_scene)
    {
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(&a_scene);
        Illustrator ilustrator;
        ilustrator.draw_scoreboard(*score_scrn, window);
    }

    void Game_Window::draw_scene(Player& a_player, Scene& a_scene)
    {  
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                draw_title_screen(a_scene);
                break;
            case GameState::Level1:
                draw_level_one(a_player, a_scene);
                break;
            case GameState::ScoreBoard:
                draw_scoreboard(a_player, a_scene);
                break;
            case GameState::Paused:
                break;
        }
    }

    void Game_Window::run_title_screen(Player& a_player, Scene& a_scene)
    {
        handleCollisions(a_player, a_scene);
        draw_background(a_scene);
        draw_scene(a_player, a_scene);
        window.display();
    }

    void Game_Window::run_level_one(Player& a_player, Scene& a_scene)
    {
        handleCollisions(a_player, a_scene);
        draw_background(a_scene);
/* 
        window.draw(*border);
        window.draw(*kill_zone);
        draw_shapes();
*/
        draw_scene(a_player, a_scene);
        animate_balls(a_scene);
        draw_score(a_player.get_score());
        win_condition(a_player);

        window.display();
    }

    void Game_Window::run_scoreboard_screen(Player& a_player, Scene& a_scene)
    {
        draw_background(a_scene);
        draw_scene(a_player, a_scene);
        window.display();
    }

    void Game_Window::run(Player& a_player, Scene& a_scene) //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    {
        while (window.isOpen())
        {   
            processEvents(a_player, a_scene);
            switch (currentGameState)
            {
                case GameState::TitleScreen:
                    run_title_screen(a_player, a_scene);
                    break;
                case GameState::Level1:
                    run_level_one(a_player, a_scene);
                    break;
                case GameState::ScoreBoard:
                    run_scoreboard_screen(a_player, a_scene);
                    break;
                case GameState::Paused:
                    break;
            }
        }
    }

    void Game_Window::restart(Scene& a_scene)
    {
        window.clear();
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        level_one->reset();
    }

    void Game_Window::win_condition(Player& a_player)
    {
        if(a_player.get_score() == WIN_SCORE)
        {
            game_win_screen();
        }
    }

    bool Game_Window::close_window_check(Event const& event)
    {
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
        {
            window.close();
            return true;
        }
        return false;
    }

    void Game_Window::game_win_screen()
    {
        Illustrator illustrator;
        illustrator.draw_win_screen(window);
        currentGameState = GameState::ScoreBoard;
        //make_scoreBoard_screen();
    }

    void Game_Window::game_over_screen()
    {
        Illustrator illustrator;
        illustrator.draw_game_over_screen(window);
    }

    void Game_Window::animate_balls(Scene& a_scene)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        auto balls = level_one->get_balls();
        for (const auto& ballPtr : balls)
        {
            animator->animate_ball(*ballPtr);
        }
    }

    void Game_Window::animate_paddle_right(Scene& a_scene)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        animator->animate_paddle_right(level_one->get_paddle(), clock);
    }

    void Game_Window::animate_paddle_left(Scene& a_scene)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        animator->animate_paddle_left(level_one->get_paddle(), clock);
    }

    void Game_Window::animate_paddle_stop(Scene& a_scene)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        animator->animate_paddle_stop(level_one->get_paddle());
    }

    void Game_Window::update_top_scores(Player& a_player)
    {
        ScoresFileManager sc_manager;

        std::string playerName = a_player.get_name();
        std::array<char, 32> nameArray{};
        size_t nameLength = std::min(playerName.size(), nameArray.size() - 1);
        std::copy_n(playerName.c_str(), nameLength, nameArray.begin());
        nameArray[nameLength] = '\0';

        uint32_t score = static_cast<uint32_t>(a_player.get_score());
        uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

        std::unique_ptr<PlayerData> playerData = std::make_unique<PlayerData>();
        std::memcpy((*playerData).name, nameArray.data(), nameArray.size());

        (*playerData).score = score;
        (*playerData).elapsedTimeMs = elapsedTimeMs;
        sc_manager.update_top10_file(*playerData);
    }

    void Game_Window::pause_game()
    {
        Event event;
        while(currentGameState == GameState::Paused)
        {
            draw_pause_text();
            window.display();
            while (window.pollEvent(event))
            {   
                close_window_check(event);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    currentGameState = GameState::Level1;
                    break;
                }
            }
        }
    }

    void Game_Window::paddle_movement_control(Player& a_player, Scene& a_scene, Event const& event)
    {
        Level_One* level_one = dynamic_cast<Level_One*>(&a_scene);
        auto& balls = level_one->get_balls();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space && !(level_one->get_paddle()->started()))
            {
                for(auto& ballPtr : balls)
                {
                    ballPtr->ball_start();
                }
                paddle->paddle_start();
            }
            else if (event.key.code == sf::Keyboard::Space && (paddle->started()) && paused == false)
            {
                currentGameState = GameState::Paused;
                pause_game();
            }
            else if (event.key.code == sf::Keyboard::Right && paddle->started())
            {
                animate_paddle_right();
            }
            else if (event.key.code == sf::Keyboard::Left && paddle->started())
            {
                animate_paddle_left();
            }
        }
        else if (event.type == sf::Event::KeyReleased && paddle->started())
        {
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
            {
                animate_paddle_stop();
            }
        }
    }

    void Game_Window::title_screen_button_click_handler(Player& a_player, Scene& a_scene, Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

            Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
            auto const& buttons = title_scrn->get_vector(); 

            Button& button1 = *buttons.at(0);
            Button& button2 = *buttons.at(1);

            if (button1.getBounds().contains(mousePosition))
            {                    
                currentGameState = GameState::Level1;
                make_level_one();
            }
            else if (button2.getBounds().contains(mousePosition))
            {
                window.close();
            }
        }
    }

    std::string Game_Window::input_name()
    {
        Text text("New high score!\n input name:", font, 50);
        text.setFillColor(Color::White);
        text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/4);
        Text inputText("", font, 30);
        std::string playerName;
        inputText.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3 + 100);
        inputText.setFillColor(Color::Cyan);

        bool quit = false;
        Event event;
        while(window.isOpen())
        {
            while (window.pollEvent(event)) 
            {
                close_window_check(event);
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
                {
                    quit = true;
                    high_score = false;
                    break;
                }
                else if (event.type == sf::Event::TextEntered) 
                {
                    if (event.text.unicode < 128 && playerName.size() <= 16 && event.text.unicode != '\b') 
                    {
                        playerName += static_cast<char>(event.text.unicode);
                        inputText.setString(playerName);
                    } else if (event.text.unicode == '\b' && !playerName.empty()) 
                    {
                        playerName.pop_back();
                        inputText.setString(playerName);
                    }
                }
            }
            window.clear(Color::Black);
            window.draw(text);
            window.draw(inputText);
            window.display();

            if(quit)
            {
                break;
            }
        }
        return playerName;
    }        

    void Game_Window::paddle_out_of_bounds_handler(Player& a_player, Scene& a_scene)
    {
        Paddle& pad = *paddle;
        FloatRect paddleBounds = pad.getGlobalBounds();
        FloatRect borderBounds = (*border).getGlobalBounds();
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

    void Game_Window::new_high_score_check(Player& a_player, Scene& a_scene)
    {
        uint32_t score = static_cast<uint32_t>(player->get_score());
        uint64_t elapsedTimeMs = static_cast<uint64_t>(clock.getElapsedTime().asMilliseconds());

        PlayerData new_player{"", score, elapsedTimeMs};
        ScoresFileManager score_manager;

        if(!high_score_entered && score_manager.check_new_high_score(new_player))
        {
            high_score = true;
            player->set_name(input_name());
            update_top_scores();
            make_scoreBoard_screen();
            high_score_entered = true;
        }
    }

   void Game_Window::restart_game_handler(Player& a_player, Scene& a_scene, Event const& event)
    {
        if ((event.type == Event::KeyPressed && event.key.code != Keyboard::Escape))
        {
            restart();
            make_title_screen();
        }
    }

    void Game_Window::processEvents(Player& a_player, Scene& a_scene)
    {
        Event event;
        while (window.pollEvent(event))
        {   
            close_window_check(event);
            switch (currentGameState)
            {
                case GameState::TitleScreen:
                    title_screen_button_click_handler(event);
                    break;
                case GameState::Level1:
                    paddle_movement_control(event);
                    break;
                case GameState::ScoreBoard:
                    new_high_score_check();
                    restart_game_handler(event);
                    break;
                case GameState::Paused:
                    break;
            }
        }
    }

    void Game_Window::level_one_collisions_handler(Player& a_player, Scene& a_scene)
    {
        Paddle& pad = *paddle;
        Level_One* level_1 = dynamic_cast<Level_One*>(scene.get());
        auto& blocks = level_1->get_vector(); 

        paddle_out_of_bounds_handler();

        for (const auto& ballPtr : balls)
        {
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
                if(check_collision(*ballPtr, *block))
                {
                    player->add_score(40);
                    ball_block_collision_handler(*block, *ballPtr);//will vanish a block
                }
            }

            ball_window_collision_handler(*ballPtr, window);    
            ball_paddle_collision_handler(*ballPtr,pad);

            if(ball_kill_zone_collision_handler(*ballPtr, *kill_zone))  // will vanish a ball , wont delete it from the vector
            {
                player->hit();
                if(player->is_dead())
                {
                    game_over_screen();
                }
                ballPtr->reset();
                paddle_reset();

                balls.erase(balls.begin()); // will delete the pointer from the vector, the smart pointer will handle the memory
                spawn_ball();
            }
        }
    }

    void Game_Window::handleCollisions(Player& a_player, Scene& a_scene)
    {
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                break;
            case GameState::Level1:
                level_one_collisions_handler();
                break;
            case GameState::ScoreBoard:
                break;
            case GameState::Paused:
                break;
        }
    }

} // namespace arkanoid
