#include "mu_test.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace sfml_test
{
    class Make_window
    {
    public:
        Make_window() : window(sf::VideoMode(800, 600), "SFML Window") 
        {
        }

        void run()
        {
            while (window.isOpen())
            {
                processEvents();
            }
        }

        ~Make_window() = default;

    private:
        sf::RenderWindow window;

        void processEvents()
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    break; 
                }
            }
        }

    };
} // namespace sfml_test


BEGIN_TEST(window_test)
    sfml_test::Make_window window;
    window.run();
    ASSERT_THAT(true);
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(window_test)
END_SUITE
