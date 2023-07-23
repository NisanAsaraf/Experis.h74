#ifndef CONFIG_H
#define CONFIG_H

inline const int SCREEN_WIDTH = 800;
inline const int SCREEN_HEIGHT = 600;
inline const int WIN_SCORE = 600;

enum class GameState
{
    TitleScreen,
    Level1,
    ScoreBoard,
    Paused,
};

#endif//CONFIG_H
