#ifndef SCENE_H
#define SCENE_H
#include "abs_scene.hpp"


namespace arkanoid
{

enum class GameState
{
    TitleScreen,
    Level,
    ScoreBoard,
    Paused,
};

class Title_Screen : public Scene
{
public:
    Title_Screen();
    void create() override;
    void reset() override;
};


class Level_One : public Scene
{
public:
    Level_One();
    void create() override;
    void reset() override;
private:
    void make_blocks(); 
};

class Level_Two : public Scene
{
public:
    Level_Two();
    void create() override;
    void reset() override;
private:
    void make_blocks(); 
};

class Level_Three : public Scene
{
public:
    Level_Three();
    void create() override;
    void reset() override;
private:
    void make_blocks(); 
};

class Level_Four : public Scene
{
public:
    Level_Four();
    void create() override;
    void reset() override;
private:
    void make_blocks(); 
};


class Score_Board : public Scene
{
public:
    Score_Board(std::vector<PlayerData>&);
    void create() override;
    void reset() override;
private:
    std::vector<PlayerData> m_players;
};

}
#endif //SCENE_H