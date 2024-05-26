#pragma once

#include <SFML/Audio.hpp>

class Audio
{
public:
    // Constructor
    Audio();

    // Background music
    sf::Music bg_music;

    // Sound effects
    sf::Sound movement_sound, rotate_sound, block_placed_sound, row_cleared_sound;
    sf::Sound gameover_sound, highscore_sound;

private:
    // Sound buffers
    sf::SoundBuffer movement_sound_buffer, rotate_sound_buffer, block_placed_sound_buffer, row_cleared_sound_buffer;
    sf::SoundBuffer gameover_sound_buffer, highscore_sound_buffer;

    // Initialize sound resources
    void initializeSound();
};
