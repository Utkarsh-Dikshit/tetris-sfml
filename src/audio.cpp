#include "header/audio.h"

Audio::Audio()
{
    // Load background music from file
    bg_music.openFromFile("resources/sounds/InnerBg.mp3");

    // Load sound effect buffers
    movement_sound_buffer.loadFromFile("resources/sounds/blockMovement.ogg");
    rotate_sound_buffer.loadFromFile("resources/sounds/RotateSound.ogg");
    block_placed_sound_buffer.loadFromFile("resources/sounds/BlockPlaced.ogg");
    row_cleared_sound_buffer.loadFromFile("resources/sounds/LineCleared.ogg");

    gameover_sound_buffer.loadFromFile("resources/sounds/GameOver.wav");
    highscore_sound_buffer.loadFromFile("resources/sounds/HighScore.ogg");

    // Initialize sound resources
    initializeSound();
}

void Audio::initializeSound()
{
    // Set sound buffers for each sound effect
    movement_sound.setBuffer(movement_sound_buffer);
    rotate_sound.setBuffer(rotate_sound_buffer);
    block_placed_sound.setBuffer(block_placed_sound_buffer);
    row_cleared_sound.setBuffer(row_cleared_sound_buffer);
    gameover_sound.setBuffer(gameover_sound_buffer);
    highscore_sound.setBuffer(highscore_sound_buffer);
}
