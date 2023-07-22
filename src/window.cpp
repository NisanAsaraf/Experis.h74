#include "../inc/window.hpp"
#include <exception>
#include <memory>
#include <iostream>
#include <fstream>
namespace arkanoid
{
using namespace sf;

    Game_Window::Game_Window()
    : window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)
    ,"Arkanoid",Style::Titlebar | Style::Close)
    ,currentGameState(GameState::TitleScreen)
    ,paused(false)
    ,high_score(false)
    { 
        create_player();
        if (!font.loadFromFile("/home/nisan/Experis.h74/assets/fonts/Antonio-Bold.ttf"))
        {
            throw std::runtime_error("Failed to load font from file.");
        }

        window.setFramerateLimit(64);
        window.setVerticalSyncEnabled(false);
        make_title_screen();
        //make_level_one()
        //make_scoreBoard_screen();
    }

    void Game_Window::make_level_one()
    {
        currentGameState = GameState::Level1;
        clock.restart();
        scene = std::make_unique<Level_One>();
        Level_One* level_1 = dynamic_cast<Level_One*>(scene.get());

        level_1->create();
        make_border();
        make_kill_zone();
        make_paddle();
        spawn_ball();
    }
    
    void Game_Window::make_title_screen()
    {
        currentGameState = GameState::TitleScreen;
        scene = std::make_unique<Title_Screen>();
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
        title_scrn->create();
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

    void Game_Window::create_player()
    {
        player = std::make_unique<Player>();
    }

    void Game_Window::make_paddle()
    {
        paddle = std::make_unique<Paddle>();
    }

    void Game_Window::make_kill_zone()
    {
        kill_zone = std::make_unique<RectangleShape>(Vector2f(window.getSize()));
        kill_zone->setPosition(0, window.getSize().y - 10);
        kill_zone->setFillColor(Color::Transparent);
    }

    void Game_Window::make_border()
    {
        float borderWidth = window.getSize().x - 10.0f ;
        float borderHeight = window.getSize().y - 10.0f ;
        sf::Color Teal(0, 128, 128);

        border = std::make_unique<sf::RectangleShape>(Vector2f(borderWidth, borderHeight));
        border->setFillColor(Color::Transparent);

        border->setPosition(5.0f, 5.0f);
        border->setOutlineThickness(5.0f);
        border->setOutlineColor(Teal);
    }

    void Game_Window::spawn_ball()
    {
        balls.emplace_back(std::make_unique<Ball>());
    }

    void Game_Window::paddle_reset()
    {
        paddle->reset();
    }

    void Game_Window::run_level_one()
    {
        handleCollisions();
        draw_background();
        window.draw(*border);
        window.draw(*kill_zone);
        draw_shapes();
        draw_scene();
        animate_balls();
        draw_score();
        win_condition();
        window.display();
    }

    void Game_Window::draw_background_level_one()
    {
        Level_One* level_1 = dynamic_cast<Level_One*>(scene.get());
        Sprite backgroundSprite;
        backgroundSprite.setTexture(*(level_1->get_BG()));     
        window.clear();
        backgroundSprite.setScale(0.2f, 0.2f);
        window.draw(backgroundSprite);
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
        }
    }

    void Game_Window::draw_background_title_screen()
    {
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
        Sprite backgroundSprite;
        window.clear();
        backgroundSprite.setTexture(*(title_scrn->get_BG()));     
        backgroundSprite.setScale(0.2f, 0.2f);
        window.draw(backgroundSprite);
    }

    void Game_Window::run_title_screen()
    {
        handleCollisions();
        draw_background();
        draw_scene();
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
            }
        }
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
        Text text;
        Clock clk;
        Event event;
        bool quit = false;
        text.setFont(font);
        text.setString("YOU WIN!");
        text.setCharacterSize(100);
        text.setFillColor(Color::Green);
        text.setPosition(SCREEN_WIDTH/4 + 20, SCREEN_HEIGHT/3);

        while(clk.getElapsedTime().asSeconds() < 10)
        {
            window.draw(text);
            window.display();
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                {
                    quit = true;
                    break;
                }
            }
            if(quit)
            {
                break;
            }
        }
        currentGameState = GameState::ScoreBoard;
        make_scoreBoard_screen();
    }

    void Game_Window::game_over_screen()
    {
        Text text;
        Clock clk;
        Event event;
        bool quit = false;

        text.setFont(font);
        text.setString("GAME OVER!");
        text.setCharacterSize(100);
        text.setFillColor(Color::Red);
        text.setPosition(SCREEN_WIDTH/4 - 20, SCREEN_HEIGHT/3 );

        while(clk.getElapsedTime().asSeconds() < 20)
        {
            window.draw(text);
            window.display();
            while (window.pollEvent(event))
            {
                quit = close_window_check(event);
            }
            if(quit)
            {
                break;
            }          
        }
    }

    void Game_Window::restart()
    {
        player->reset();
        paddle_reset();
        balls.clear();
        scene->reset();
        make_level_one();
        spawn_ball();
    }

    void Game_Window::animate_balls()
    {
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *ballPtr;
            ball.move(ball.getVelocity());
        }
    }

    void Game_Window::animate_paddle_right()
    {
        Paddle& pad = *paddle;
        pad.right(clock);
        pad.move(pad.getVelocity());
    }

    void Game_Window::animate_paddle_left()
    {
        Paddle& pad = *paddle;
        pad.left(clock);
        pad.move(pad.getVelocity());
    }

    void Game_Window::animate_paddle_stop()
    {
        Paddle& pad = *paddle;
        pad.stop();
        pad.move(pad.getVelocity());
    }

    void Game_Window::draw_shapes()
    {
        Paddle& pad = *paddle;
        draw_shape(pad, window);      
        for (const auto& ballPtr : balls)
        {
            Ball& ball = *ballPtr;
            draw_shape(ball, window);
        }
    }

    void Game_Window::draw_hearts()
    {
        size_t lives = player->get_lives();
        for (size_t i = 1; i <= lives; i++)
        {
            Life life(Vector2f(30*i, 70));
            window.draw(*(life.get()));
        }
    }

    void Game_Window::draw_level_one()
    {
        Level_One* level_1 = dynamic_cast<Level_One*>(scene.get());
        auto const& blocks = level_1->get_vector();
        for (auto& blockPtr : blocks)
        { 
            Block& block = *blockPtr;
            draw_shape(block, window);
        }
        draw_hearts();
    }
    
    void Game_Window::Game_Window::draw_background_score_board()
    {
        Score_Board* score_scrn = dynamic_cast<Score_Board*>(scene.get());
        Illustrator illustrator;
        illustrator.draw_BG_scoreboard(*score_scrn,window);
    }

    void Game_Window::draw_title_screen()
    {
        Title_Screen* title_scrn = dynamic_cast<Title_Screen*>(scene.get());
        auto const& buttons = title_scrn->get_vector();
        window.draw(title_scrn->getTitleText());

        for (auto& buttonPtr : buttons)
        {
            Button& button = *buttonPtr;
            draw_shape(button, window);
            window.draw(button.getText());
        }
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
        }
    }

    void Game_Window::draw_score()
    {
        Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(player->get_score()));

        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(30, 30);
        window.draw(scoreText);
    }

    void Game_Window::draw_pause_text()
    {
        Text text;
        text.setFont(font);
        text.setString("PAUSED");

        text.setCharacterSize(100);
        text.setFillColor(Color::White);
        text.setPosition(SCREEN_WIDTH/3, SCREEN_HEIGHT/3);
        window.draw(text);
    }

    void Game_Window::update_top_scores()
    {
        ScoresFileManager sc_manager;
        std::unique_ptr<PlayerData> p_data = std::make_unique<PlayerData>();
        *p_data = {player->get_name() , player->get_score(), clock.getElapsedTime().asSeconds()};
        sc_manager.update_top10_file(*p_data);
    }

    void Game_Window::pause_game()
    {
        Event event;
        while(paused)
        {
            draw_pause_text();
            window.display();
            while (window.pollEvent(event))
            {   
                close_window_check(event);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    paused = false;
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
                paused = true;
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
                    make_title_screen();
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

    void Game_Window::new_high_score_check()
    {
        //PlayerData new_player{"", player->get_score(), clock.getElapsedTime()};
        //ScoresFileManager score_manager;

        if(true /* score_manager.check_new_high_score(new_player) */ )
        {
            high_score = true;
            player->set_name(input_name());
            update_top_scores();
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
                    break;
            }
        }
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
        }
    }

} // namespace arkanoid
