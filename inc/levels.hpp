#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include "block.hpp"
#include <vector>

namespace arkanoid
{

/* class Level
{
public:
    virtual ~Level();
};
 */
class Level_One //: Level
{
public:

    Level_One(size_t row, size_t col);

    std::vector<std::unique_ptr<Block>>& get_blocks();
    void reset();

    ~Level_One() = default;

private:
    std::vector<std::unique_ptr<Block>> blocks;
};

}
#endif //LEVEL_H