#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

namespace arkanoid
{
using namespace sf;

class Block
{
public:
    Block(Color, float , float);
    FloatRect getGlobalBounds();
    Vector2f getSize();
    bool isVanished();
    const RectangleShape& getShape() const;
    void Collision() ;
private:
    void vanish();

private:
    std::unique_ptr<RectangleShape> shape;
    bool vanished;

};

}//namespace arkanoid
#endif //BLOCK_H