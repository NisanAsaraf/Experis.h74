#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "collisions.hpp"

namespace arkanoid
{
using namespace sf;

class Block : Collidable
{
public:
    Block(Color, float , float);
    FloatRect getGlobalBounds() override;
    const RectangleShape& getShape() const;
    void Collision() override;
private:
    void vanish();

private:
    std::unique_ptr<RectangleShape> shape;
    bool vanished;

};

}//namespace arkanoid
#endif //BLOCK_H