#pragma once

#include "grid.h"
#include "block.h"
#include "..\\blocks.cpp" // Note: Double backslashes for Windows path
#include "audio.h"

class Game
{
public:
    Game();
    ~Game();

    // Minimum screen dimensions
    int minimum_screen_width;
    int minimum_screen_height;

    // Draw the game on the specified window
    void drawGame(sf::RenderWindow& window);

    // Update drawable entities (e.g., blocks, grid) on the window
    void updateDrawableEntity(sf::RenderWindow& window);

    // Handle user input
    void inputHandler(sf::RenderWindow& window);

private:
    // Position variables for movable and fixed entities
    int set_pos_x_moveable_block;
    int set_pos_y_moveable_block;
    int set_pos_x_fix_entity;
    int set_pos_y_fix_entity;

    // Game state variables
    bool gameover;
    bool is_key_pressed_once;

    // Clock for timing
    sf::Clock clock;

    // Grid and audio objects
    Grid grid;
    Audio audio;

    // Block management
    std::vector<Block> all_blocks;
    Block curr_block, next_block;

    // Get all available block types
    std::vector<Block> getAllBlocks();

    // Get a random block
    Block getRandomBlock();

    // Initialize game entities
    void initializeEntities();

    // Movement and rotation functions
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateBlock();

    // Check if the current block is outside the grid
    bool isBlockOutside();

    // Check if the current block has free space to move
    bool isCurrBlockSpaceFree();

    // Fix the current block in place
    void fixBlock();

    // Ghost block management
    int ghost_block_curr_row;
    void moveGhostBlockDOWN();
    void setGhostBlockPosition();
    bool isBelowRowEmpty();

    // Background scrolling speed
    float scrolling_bg;

    // Texture for the background
    sf::Texture bg_texture;

    // Fonts and text objects
    sf::Font font;
    sf::Text score_text, highscore_text, next_block_text;
    sf::Text score_value_text, highscore_value_text;

    // Rectangle shapes for UI elements
    sf::RectangleShape bg_rec_1, bg_rec_2;
    sf::RectangleShape score_rec, highscore_rec, next_block_rec;

    // High score management
    bool is_highscore_updated;
    int score, high_score;
    void getHighScore();
    void updateScore(int num_completed_row, int num_block_move_down);
    void updateHighScore();

    // Reset the game
    void resetGame();
};
