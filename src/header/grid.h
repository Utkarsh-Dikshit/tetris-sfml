#pragma once

#include <SFML/Graphics.hpp>
#include "color.h"

class Grid
{
public:
    Grid();
    int grid[20][10];
    int cell_size;

    // Draw the grid on the window
    void drawGrid(sf::RenderWindow &window, int move_in_x, int move_in_y);

    // Check if a cell is outside the grid boundaries
    bool isCellOutside(int row, int column);

    // Clear full rows and return the number of cleared rows
    int clearFullRow();

    // Initialize the grid (set all cells to empty)
    void initializeGrid();

private:
    int num_rows, num_col;
    int rotation_state;

    std::vector<sf::Color> cell_color;

    sf::RectangleShape grid_border;

    // Check if a row is full (all cells are filled)
    bool isRowFull(int row);

    // Clear a specific row (set all cells to empty)
    void clearRow(int row);

    // Move a row down by a specified number of rows
    void moveRowDown(int row, int move_by_row);
};
