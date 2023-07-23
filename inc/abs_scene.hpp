#ifndef ABS_SCENE_H
#define ABS_SCENE_H

namespace arkanoid
{
    
class Scene
{
public:
    virtual void create() = 0;
    virtual void reset() = 0;
};

}//namespace arkanoid

#endif