#include "header/grid.h"

Grid::Grid()
{
    // Initialize grid properties
    num_rows = 20;
    num_col = 10;
    cell_size = 30;
    initializeGrid();
    cell_color = getOuterCellColors();
}

void Grid::initializeGrid()
{
    // Initialize the grid with empty cells
    for (int i = 0; i < num_rows; ++i)
    {
        for (int j = 0; j < num_col; ++j)
        {
            grid[i][j] = 0;
        }
    }
    // Initialize the grid border
    grid_border.setSize(sf::Vector2f(300.0f, 600.0f));
    grid_border.setFillColor(sf::Color::Transparent);
    grid_border.setOutlineColor(sf::Color::White);
    grid_border.setOutlineThickness(3);
}

void Grid::drawGrid(sf::RenderWindow &window, int move_in_x, int move_in_y)
{
    // Draw the grid border
    grid_border.setPosition(sf::Vector2f(move_in_x + 11, move_in_y + 11));
    window.draw(grid_border);

    // Draw individual cells
    for (int i = 0; i < num_rows; ++i)
    {
        for (int j = 0; j < num_col; ++j)
        {
            int cell_value = grid[i][j];
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cell_size - 1), static_cast<float>(cell_size - 1)));
            cell.setPosition(sf::Vector2f(static_cast<float>(move_in_x + j * cell_size + 11),
                                          static_cast<float>(move_in_y + i * cell_size + 11)));
            cell.setFillColor(cell_color[cell_value]);
            window.draw(cell);
        }
    }
}

bool Grid::isCellOutside(int row, int column)
{
    // Check if a cell is outside the grid boundaries
    return (row < 0 || row >= num_rows || column < 0 || column >= num_col);
}

bool Grid::isRowFull(int row)
{
    // Check if a row is completely full
    for (int col = 0; col < num_col; col++)
    {
        // if any cell == 0, then not completely filled
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int row)
{
    // Clear all cells in a row
    for (int col = 0; col < num_col; ++col)
    {
        grid[row][col] = 0;
    }
}

void Grid::moveRowDown(int row, int move_by_row)
{
    // Move a row down by a specified number of rows
    for (int col = 0; col < num_col; ++col)
    {
        grid[row + move_by_row][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

int Grid::clearFullRow()
{
    // Clear completed full rows and shift rows down
    int completed_row = 0;
    for (int row = num_rows - 1; row >= 0; --row)
    {
        if (isRowFull(row))
        {
            ++completed_row;
            clearRow(row);
        }
        else if (completed_row > 0)
        {
            moveRowDown(row, completed_row);
        }
    }
    return completed_row;
}