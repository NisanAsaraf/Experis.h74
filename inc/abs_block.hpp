#ifndef ABS_BLOCK_H
#define ABS_BLOCK_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace arkanoid
{
class Block
{
public:
    Block(float a_x, float a_y);
    Block(sf::Vector2f a_pos);
    virtual ~Block() = default;
    int getScoreValue(size_t a_lvl = 1) const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getSize() const ;
    const sf::RectangleShape& getShape() const;
    bool isVanished() const ;
    bool isExplode() const;
    virtual void collision() = 0;
private:
    void make_base(float x , float y);
protected:
    void vanish();
    std::unique_ptr<sf::RectangleShape> shape;
    std::unique_ptr<sf::Texture> blockTexture;
    int score_modifer; //basically a 0 or 1 to handle the gray blocks
    int score;
    bool is_explode;
    bool vanished;
};

}//arkanoid


#endif