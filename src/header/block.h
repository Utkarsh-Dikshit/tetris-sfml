#pragma once

#include <SFML/Graphics.hpp>
#include "color.h"
#include <vector>
#include <map>

class Block
{
public:
    // Constructor
    Block();

    // Unique identifier for the block
    int block_id;

    // Offset for the ghost block's row
    int row_offset_ghost_block;

    // Mapping of block cells (row, column) for different rotation states
    std::map<int, std::vector<sf::Vector2i>> block_cell;

    // Get positions of active block cells
    std::vector<sf::Vector2i> getCellPosition();

    // Get positions of ghost block cells
    std::vector<sf::Vector2i> getcellPositionForGhostBLock();

    // Move the block by specified rows and columns
    void moveBlock(int move_by_row, int move_by_col);

    // Move the ghost block by specified rows
    void moveGhostBlock(int move_by_rows);

    // Rotate the block
    void rotate();

    // Undo the last rotation
    void undoRotation();

    // Draw the active block
    void drawBlock(sf::RenderWindow &window, int move_in_x, int move_in_y, int align);

    // Draw the ghost block
    void drawGhostBlock(sf::RenderWindow &window, int move_in_x, int move_in_y, int align);

private:
    int cell_size;
    int row_offset, col_offset;
    int rotation_state;

    std::vector<sf::Color> outer_color;
    std::vector<sf::Color> inner_color;
};
