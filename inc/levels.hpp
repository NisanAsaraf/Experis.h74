#ifndef LEVEL_
#define LEVEL_
#include <SFML/Graphics.hpp>
#include <vector>

namespace arkanoid
{

class Level
{
    virtual void setup(size_t , size_t);
};

class Level_One : Level
{
public:
    void setup(size_t row, size_t col) override;
private:
    std::vector<std::unique_ptr<sf::RectangleShape>> blocks;
};

}
#endif //LEVEL_