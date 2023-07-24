#ifndef ABS_SCENE_H
#define ABS_SCENE_H

namespace arkanoid
{
    
class Scene
{
public:
    virtual void create() = 0;
    virtual void reset() = 0;
    virtual size_t get_win_score() const = 0;
};

}//namespace arkanoid

#endif