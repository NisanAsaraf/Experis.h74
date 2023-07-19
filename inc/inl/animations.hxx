#ifndef ANIME_HXX
#define ANIME_HXX
#include "../animations.hpp"

namespace arkanoid
{
using namespace sf;

template <typename T>
void draw_shape(T& a_object, RenderWindow& a_window)
{
    a_window.draw(a_object.getShape());
}

}//namespace arkanoid

#endif // ANIME_HXX