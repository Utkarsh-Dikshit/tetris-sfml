#include "header/game.h"
#include <iostream>
#include <fstream>
#include <string>

Game::Game()
{
    // Initialize minimum screen dimensions
    minimum_screen_width = 640;
    minimum_screen_height = 620;

    // Initialize block types and other game variables
    all_blocks = getAllBlocks();
    curr_block = getRandomBlock();
    next_block = getRandomBlock();

    scrolling_bg = 0.0;

    is_key_pressed_once = false;
    gameover = false;

    score = 0;
    high_score = 0;
    is_highscore_updated = false;

    ghost_block_curr_row = 0;
    initializeEntities();
}

Game::~Game()
{
    // Store HighScore Back to File
    std::ofstream outfile("resources/data.txt");
    if (outfile.is_open())
    {
        outfile << high_score;
        outfile.close();
    }
}

void Game::getHighScore()
{
    // Read high score from file
    std::ifstream file("resources/data.txt");
    if (file.is_open())
    {
        file >> high_score;
        file.close();
    }
}

void Game::initializeEntities()
{
    // Load high score and set up game entities
    getHighScore();

    audio.bg_music.play();
    audio.bg_music.setLoop(true);

    bg_texture.loadFromFile("resources/Images/bg2.png", sf::IntRect(0, 0, bg_texture.getSize().x, bg_texture.getSize().y));

    bg_rec_1.setTexture(&bg_texture);
    bg_rec_2.setTexture(&bg_texture);

    font.loadFromFile("resources/font/font.ttf");

    // Set up UI elements
    score_rec.setSize(sf::Vector2f(167, 50));
    score_rec.setFillColor(lightBlue);

    highscore_rec.setSize(sf::Vector2f(167, 50));
    highscore_rec.setFillColor(lightBlue);

    next_block_rec.setSize(sf::Vector2f(200, 140));
    next_block_rec.setFillColor(lightBlue);

    score_text = sf::Text("SCORE", font, 29);
    highscore_text = sf::Text("HIGH SCORE", font, 29);
    next_block_text = sf::Text("NEXT BLOCK", font, 29);

    score_value_text = sf::Text(std::to_string(score), font, 25);
    highscore_value_text = sf::Text(std::to_string(high_score), font, 25);

    score_text.setFillColor(sf::Color::White);
    highscore_text.setFillColor(sf::Color::White);
    next_block_text.setFillColor(sf::Color::White);

    score_value_text.setFillColor(sf::Color::White);
    highscore_value_text.setFillColor(sf::Color::White);
}

void Game::drawGame(sf::RenderWindow &window)
{
    // Draw background, grid, current block, and next block
    window.draw(bg_rec_1);
    window.draw(bg_rec_2);

    window.draw(score_rec);
    window.draw(highscore_rec);
    window.draw(next_block_rec);

    window.draw(score_text);
    window.draw(highscore_text);
    window.draw(next_block_text);

    window.draw(score_value_text);
    window.draw(highscore_value_text);

    grid.drawGrid(window, set_pos_x_moveable_block, set_pos_y_moveable_block);

    curr_block.drawBlock(window, set_pos_x_moveable_block, set_pos_y_moveable_block, 11);

    // I-Block
    if (next_block.block_id == 3)
    {
        next_block.drawBlock(window, next_block_rec.getPosition().x + ((next_block_rec.getSize().x - (grid.cell_size * 4)) / 2) - 90, next_block_rec.getPosition().y + ((next_block_rec.getSize().y - (grid.cell_size * 1)) / 2), 0);
    }
    // O-Block
    else if (next_block.block_id == 4)
    {
        next_block.drawBlock(window, next_block_rec.getPosition().x + ((next_block_rec.getSize().x - (grid.cell_size * 2)) / 2) - 120, next_block_rec.getPosition().y + ((next_block_rec.getSize().y - (grid.cell_size * 2)) / 2), 0);
    }
    else
    {
        next_block.drawBlock(window, next_block_rec.getPosition().x + ((next_block_rec.getSize().x - (grid.cell_size * 3)) / 2) - 90, next_block_rec.getPosition().y + ((next_block_rec.getSize().y - (grid.cell_size * 2)) / 2), 0);
    }

    setGhostBlockPosition();
    curr_block.drawGhostBlock(window, set_pos_x_moveable_block, set_pos_y_moveable_block, 11);
}

void Game::updateDrawableEntity(sf::RenderWindow& window)
{
    // Calculate positions for UI elements and background scrolling
    set_pos_x_moveable_block = (window.getSize().x - minimum_screen_width) / 2;
    set_pos_y_moveable_block = (window.getSize().y - minimum_screen_height) / 2;

    set_pos_x_fix_entity = (window.getSize().x - minimum_screen_width) / 1.5;
    set_pos_y_fix_entity = (window.getSize().y - minimum_screen_height) / 1.5;

    // Set background rectangles
    bg_rec_1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    bg_rec_2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    bg_rec_1.setPosition(sf::Vector2f(0, 0));
    bg_rec_2.setPosition(sf::Vector2f(0, window.getSize().y));

    bg_rec_1.move(sf::Vector2f(0, -scrolling_bg));
    bg_rec_2.move(sf::Vector2f(0, -scrolling_bg));

    scrolling_bg += 0.2;
    if (scrolling_bg > window.getSize().y)
    {
        scrolling_bg = 0;
    }

    // Set positions for UI elements
    score_rec.setPosition(sf::Vector2f(set_pos_x_fix_entity + 320 + 76.5, set_pos_y_fix_entity + 60));
    highscore_rec.setPosition(sf::Vector2f(set_pos_x_fix_entity + 320 + 76.5, set_pos_y_fix_entity + 180));
    next_block_rec.setPosition(sf::Vector2f(set_pos_x_fix_entity + 320 + 76.5 - 16.5, set_pos_y_fix_entity + 440));

    // Center text within UI elements
    score_text.setPosition(int(score_rec.getPosition().x + score_rec.getSize().x / 2 - score_text.getLocalBounds().width / 2), int(score_rec.getPosition().y - 2 * score_text.getLocalBounds().height));
    highscore_text.setPosition(int(highscore_rec.getPosition().x + highscore_rec.getSize().x / 2 - highscore_text.getLocalBounds().width / 2), int(highscore_rec.getPosition().y - 2 * highscore_text.getLocalBounds().height));
    next_block_text.setPosition(int(next_block_rec.getPosition().x + next_block_rec.getSize().x / 2 - next_block_text.getLocalBounds().width / 2), int(next_block_rec.getPosition().y - 2 * next_block_text.getLocalBounds().height));

    // Update score and high score text
    score_value_text.setString(std::to_string(score));
    highscore_value_text.setString(std::to_string(high_score));

    score_value_text.setPosition(int(score_rec.getPosition().x + score_rec.getSize().x / 2 - score_value_text.getLocalBounds().width / 2), int(score_rec.getPosition().y + score_rec.getSize().y / 2 - score_value_text.getLocalBounds().height));
    highscore_value_text.setPosition(int(highscore_rec.getPosition().x + highscore_rec.getSize().x / 2 - highscore_value_text.getLocalBounds().width / 2), int(highscore_rec.getPosition().y + highscore_rec.getSize().y / 2 - highscore_value_text.getLocalBounds().height));

    // Move the current block down periodically
    if (clock.getElapsedTime().asMilliseconds() >= 1200 && !gameover)
    {
        moveDown();
        clock.restart();
    }

    // Update ghost block position
    ghost_block_curr_row = curr_block.row_offset_ghost_block;
    curr_block.row_offset_ghost_block = 0;
}


std::vector<Block> Game::getAllBlocks()
{
    // Return a vector containing all available block types
    return {IBlock{}, JBlock{}, LBlock{}, OBlock{}, SBlock{}, ZBlock{}, TBlock{}};
}

Block Game::getRandomBlock()
{
    if (all_blocks.empty())
    {
        // If all_blocks is empty, refill it with all available blocks
        all_blocks = getAllBlocks();
    }

    // Get a random block from the list
    int random_index = rand() % all_blocks.size();
    Block block = all_blocks[random_index];
    all_blocks.erase(all_blocks.begin() + random_index);

    return block;
}

void Game::moveLeft()
{
    // Move the current block left
    if (!gameover)
    {
        curr_block.moveBlock(0, -1);

        if (isBlockOutside() || !isCurrBlockSpaceFree())
        {
            curr_block.moveBlock(0, 1);
        }
        else
        {
            audio.movement_sound.play();
        }
    }
}

void Game::moveRight()
{
    // Move the current block right
    if (!gameover)
    {
        curr_block.moveBlock(0, 1);

        if (isBlockOutside() || !isCurrBlockSpaceFree())
        {
            curr_block.moveBlock(0, -1);
        }
        else
        {
            audio.movement_sound.play();
        }
    }
}

void Game::moveDown()
{
    // Move the current block down
    if (!gameover)
    {
        curr_block.moveBlock(1, 0);
        if (isBlockOutside() || !isCurrBlockSpaceFree())
        {
            curr_block.moveBlock(-1, 0);
            fixBlock();
        }
        else
        {
            audio.movement_sound.play();
        }
    }
}

void Game::rotateBlock()
{
    // Rotate the current block
    if (!gameover)
    {
        curr_block.rotate();
        if (isBlockOutside() || !isCurrBlockSpaceFree())
        {
            curr_block.undoRotation();
        }
        else
        {
            audio.rotate_sound.play();
        }
    }
}

bool Game::isBlockOutside()
{
    // Check if any part of the current block is outside the grid boundaries
    for (const auto& cell : curr_block.getCellPosition())
    {
        if (grid.isCellOutside(cell.x, cell.y))
        {
            return true;
        }
    }
    return false;
}

bool Game::isCurrBlockSpaceFree()
{
    // Check if all cells of the current block are unoccupied
    for (const auto& cell : curr_block.getCellPosition())
    {
        if (grid.grid[cell.x][cell.y] != 0)
        {
            return false;
        }
    }
    return true;
}

void Game::inputHandler(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            // Close the window when the user clicks the close button
            window.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            // Handle window resizing
            sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visible_area));

            // Enforce minimum screen dimensions
            if (event.size.width < minimum_screen_width || event.size.height < minimum_screen_height)
            {
                window.setSize(sf::Vector2u(minimum_screen_width, minimum_screen_height));
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            // Handle key presses
            if (event.key.scancode == sf::Keyboard::Scan::Right)
            {
                moveRight();
            }
            if (event.key.scancode == sf::Keyboard::Scan::Left)
            {
                moveLeft();
            }
            if (event.key.scancode == sf::Keyboard::Scan::Down)
            {
                moveDown();
                updateScore(0, 1);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Up && !is_key_pressed_once)
            {
                rotateBlock();
                is_key_pressed_once = true;
            }
            if (event.key.scancode == sf::Keyboard::Scan::Space && !is_key_pressed_once)
            {
                // Move the block down to the ghost position
                curr_block.moveBlock(ghost_block_curr_row, 0);

                // Handling extreme cases for precise movement
                if (isBlockOutside() || !isCurrBlockSpaceFree())
                {
                    curr_block.moveBlock(-1, 0);
                }
                fixBlock();
                updateScore(0, 30);
                is_key_pressed_once = true;
            }
            if (event.key.scancode == sf::Keyboard::Scan::Enter && !is_key_pressed_once && gameover)
            {
                // Restart the game after game over
                gameover = false;
                resetGame();
                is_key_pressed_once = true;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            // Reset the key press flag when a key is released
            is_key_pressed_once = false;
        }
    }
}

void Game::fixBlock()
{
    // Place the current block on the grid and handle game over conditions
    std::vector<sf::Vector2i> tiles = curr_block.getCellPosition();

    for (sf::Vector2i item : tiles)
    {
        grid.grid[item.x][item.y] = curr_block.block_id;
    }

    audio.block_placed_sound.play();

    curr_block = next_block;

    if (!isCurrBlockSpaceFree())
    {
        // Game over logic
        gameover = true;
        audio.bg_music.stop();
        audio.gameover_sound.play();
    }

    next_block = getRandomBlock();

    int completed_row = grid.clearFullRow();
    if (completed_row > 0)
    {
        // Play sound and update score for completed rows
        audio.row_cleared_sound.play();
        updateScore(completed_row, 0);
    }
}

void Game::moveGhostBlockDOWN()
{
    // Move the ghost block down
    curr_block.moveGhostBlock(1);
}

void Game::setGhostBlockPosition()
{
    // Set the ghost block position to the lowest possible row
    while (isBelowRowEmpty())
    {
        moveGhostBlockDOWN();
    }
}

bool Game::isBelowRowEmpty()
{
    // Check if the row below the current block is empty
    std::vector<sf::Vector2i> tiles = curr_block.getcellPositionForGhostBLock();
    bool is_all_cell_empty = false;
    for (const auto& item : tiles)
    {
        if (grid.grid[item.x + 1][item.y] == 0 && item.x + 1 <= 19)
        {
            is_all_cell_empty = true;
        }
        else
        {
            return false;
        }
    }
    return is_all_cell_empty;
}

void Game::updateScore(int num_completed_row, int num_block_move_down)
{
    // Update the game score based on completed rows and block movement
    if (num_completed_row == 1)
    {
        score += 100;
    }
    else if (num_completed_row == 2)
    {
        score += 300;
    }
    else if (num_completed_row == 3)
    {
        score += 500;
    }
    else if (num_completed_row == 4)
    {
        score += 700;
    }
    score += num_block_move_down;
    updateHighScore();
}

void Game::updateHighScore()
{
    // Update the high score if needed and play a sound effect
    if (high_score < score)
    {
        high_score = score;
        if (!is_highscore_updated)
        {
            audio.highscore_sound.play();
        }
        is_highscore_updated = true;
    }
}

void Game::resetGame()
{
    // Reset the game state
    grid.initializeGrid();
    all_blocks = getAllBlocks();
    curr_block = getRandomBlock();
    next_block = getRandomBlock();
    score = 0;
    audio.bg_music.play();
}
