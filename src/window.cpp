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
        make_title_screen();
        //make_level_one()
        //make_scoreBoard_screen();
    }

    void Game_Window::draw_background_title_screen()
    {
        Title_Screen* title_screen_ptr = dynamic_cast<Title_Screen*>(scene.get());
        illustrator->draw_BG_title(*title_screen_ptr,window);
    }

    void Game_Window::draw_background_level_one()
    {
        Level_One* level_1 = dynamic_cast<Level_One*>(scene.get());
        illustrator->draw_BG_level(*level_1,window);
    }

    void Game_Window::Game_Window::draw_background_score_board()
    {
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(scene.get());
        Illustrator illustrator;
        illustrator.draw_BG_scoreboard(*score_scrn,window);
    }
    
    void Game_Window::draw_background()
    {
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                draw_background_title_screen();
                break;

            case GameState::Level1:
                draw_background_level_one();
                break;

            case GameState::ScoreBoard:
                draw_background_score_board();
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

    void Game_Window::draw_title_screen()
    {
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
        illustrator->draw_title_screen(*title_scrn, window);
    }

    void Game_Window::draw_level_one()
    {
        Level_One* level_one = dynamic_cast<Level_One*>(scene.get());
        illustrator->draw_level_one(*level_one, window);
        draw_hearts();
    }

    void Game_Window::draw_scoreboard()
    {
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(scene.get());
        Illustrator ilustrator;
        ilustrator.draw_scoreboard(*score_scrn, window);
    }

    void Game_Window::draw_scene()
    {  
        switch (currentGameState)
        {
            case GameState::TitleScreen:
                draw_title_screen();
                break;
            case GameState::Level1:
                draw_level_one();
                break;
            case GameState::ScoreBoard:
                draw_scoreboard();
                break;
            case GameState::Paused:
                break;
        }
    }

    void Game_Window::make_title_screen()
    {
        currentGameState = GameState::TitleScreen;
        scene = std::make_unique<Title_Screen>();
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
        title_scrn->create();
        high_score_entered = false;
    }

    void Game_Window::make_level_one()
    {
        currentGameState = GameState::Level1;
        clock.restart();

        scene = std::make_unique<Level_One>();
        Level_One* level_one = dynamic_cast<Level_One*>(scene.get());
        level_one->create();
    }
    
    void Game_Window::make_scoreBoard_screen()
    {
        currentGameState = GameState::ScoreBoard;

        std::vector<PlayerData> top_players;
        ScoresFileManager sc_manager;
        sc_manager.load_scores(top_players);

        scene = std::make_unique<Score_Board>(top_players);
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(scene.get());
        score_scrn->create();
    }

    void Game_Window::run_title_screen()
    {
        handleCollisions();
        draw_background();
        draw_scene();
        window.display();
    }

    void Game_Window::run_level_one()
    {
        handleCollisions();
        draw_background();
/* 
        window.draw(*border);
        window.draw(*kill_zone);
        draw_shapes();
*/
        draw_scene();
        animate_balls();
        draw_score();
        win_condition();
        window.display();
    }
    void Game_Window::run_scoreboard_screen()
    {
        draw_background();
        draw_scene();
        window.display();
    }

    void Game_Window::run()
    {
        while (window.isOpen())
        {   
            processEvents();
            
            switch (currentGameState)
            {
                case GameState::TitleScreen:
                    run_title_screen();
                    break;

                case GameState::Level1:
                    run_level_one();
                    break;

                case GameState::ScoreBoard:
                    run_scoreboard_screen();
                    break;
                case GameState::Paused:
                    break;
            }
        }
    }

    void Game_Window::restart()
    {
        window.clear();
        scene = std::make_unique<Level_One>();
        Level_One* level_one = dynamic_cast<Level_One*>(scene.get());
        level_one->reset();
    }

    void Game_Window::win_condition()
    {
        if(player->get_score() == WIN_SCORE)
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
        make_scoreBoard_screen();
    }

    void Game_Window::game_over_screen()
    {
        Illustrator illustrator;
        illustrator.draw_game_over_screen(window);
    }

    void Game_Window::animate_balls()
    {
        for (const auto& ballPtr : balls)
        {
            anima.animate_ball(*ballPtr);
        }
    }

    void Game_Window::animate_paddle_right()
    {
        anima.animate_paddle_right(*paddle, clock);
    }

    void Game_Window::animate_paddle_left()
    {
        anima.animate_paddle_left(*paddle, clock);
    }

    void Game_Window::animate_paddle_stop()
    {
        anima.animate_paddle_stop(*paddle);
    }

    void Game_Window::update_top_scores()
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

    void Game_Window::paddle_movement_control(Event const& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space && !(paddle->started()))
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

    void Game_Window::title_screen_button_click_handler(Event& event)
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

    void Game_Window::paddle_out_of_bounds_handler()
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

    void Game_Window::new_high_score_check()
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

   void Game_Window::restart_game_handler(Event const& event)
    {
        if ((event.type == Event::KeyPressed && event.key.code != Keyboard::Escape))
        {
            restart();
            make_title_screen();
        }
    }

    void Game_Window::processEvents()
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

    void Game_Window::level_one_collisions_handler()
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

    void Game_Window::handleCollisions()
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
