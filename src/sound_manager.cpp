#include "sound_manager.hpp"

namespace arkanoid
{

Sound_Effect::Sound_Effect(const std::string& filename)
{
    if(!soundBuffer.loadFromFile("../../assets/audio/" + filename))
    {
        throw std::runtime_error("Error opening sound file");
    }
    soundEffect.setBuffer(soundBuffer);
}

void Sound_Effect::play_sound()
{
    soundEffect.play();
}

Sound_Manager::Sound_Manager()
:block_collision{"block_collision_sound.ogg"}
,win_level{"game_win_sound.ogg"}
,lose_game{"game_over_sound.ogg"}
,gift_sound{"gift_sound.ogg"}
,is_mute{false}
{
}

void Sound_Manager::set_scene_music(const std::string& filename)
{
    if (!scene_music.openFromFile("../../assets/audio/" + filename))
    {
        throw std::runtime_error("Failed to load font from file.");
    }
}
void Sound_Manager::set_scene_volume(float a_vol)
{
    scene_music.setVolume(a_vol);
}

void Sound_Manager::play_scene_music()
{
    if(!is_mute)
    {
        scene_music.play();
    }
}

void Sound_Manager::stop_scene_music()
{
    scene_music.stop();
}

void Sound_Manager::play_block_collision_sound()
{
    if(!is_mute)
    {
        block_collision.play_sound();
    }
}

void Sound_Manager::play_win_game_sound()
{
    if(!is_mute)
    {
        win_level.play_sound();
    }
}

void Sound_Manager::play_lose_game_sound()
{
    if(!is_mute)
    {
        lose_game.play_sound();
    }
}

bool Sound_Manager::is_sound_muted()
{
    return is_mute;
}

bool Sound_Manager::mute_sound()
{
    if(is_mute == false)
    {
        is_mute = true;
        scene_music.pause();       
    }
    else
    {
        is_mute = false;
        scene_music.play();
    }
    return is_mute;
}

void Sound_Manager::play_gift_sound()
{
    gift_sound.play_sound();
}
}//namespace arkanoid



