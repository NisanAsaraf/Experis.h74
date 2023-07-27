#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <vector>
namespace arkanoid
{

class Sound_Effect
{
public:
    Sound_Effect(std::string const& filename);
    void play_sound();
private:
    sf::SoundBuffer soundBuffer;
    sf::Sound soundEffect;
};

class Sound_Manager
{
public:
    Sound_Manager();
    void set_scene_music(const std::string& filename);
    void set_scene_volume(float a_vol);
    void stop_scene_music();
    void play_scene_music();
    void play_block_collision_sound();
    void play_explosion_sound();
    void play_win_game_sound();
    void play_lose_game_sound();
    void play_gift_sound();
    bool is_sound_muted();
    bool mute_sound();
private:
    sf::Music scene_music;
    Sound_Effect block_collision;
    Sound_Effect win_level;
    Sound_Effect lose_game;
    Sound_Effect gift_sound;
    Sound_Effect explosion_sound;
    bool is_mute;
};
}//namespace arkanoid
#endif