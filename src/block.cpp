#include "header/block.h"

Block::Block()
{
    // Initialize cell size
    cell_size = 30;

    // Initialize offsets
    row_offset = 0;
    col_offset = 0;
    rotation_state = 0;

    // Get outer and inner cell colors
    outer_color = getOuterCellColors();
    inner_color = getInnerCellColors();

    // Initialize ghost block row offset
    row_offset_ghost_block = 0;
}

void Block::drawBlock(sf::RenderWindow &window, int move_in_x, int move_in_y, int align)
{
    // Get positions of active block cells
    std::vector<sf::Vector2i> tiles = getCellPosition();

    for (sf::Vector2i item : tiles)
    {
        sf::RectangleShape rec(sf::Vector2f{float(cell_size - 1), float(cell_size - 1)});

        // Set position for drawing
        rec.setPosition(sf::Vector2f{float(item.y * cell_size + move_in_x + align), float(item.x * cell_size + move_in_y + align)});

        // Set fill color and outline
        rec.setFillColor(inner_color[block_id]);
        rec.setOutlineThickness(-5.0f);
        rec.setOutlineColor(outer_color[block_id]);

        window.draw(rec);
    }
}

void Block::drawGhostBlock(sf::RenderWindow &window, int move_in_x, int move_in_y, int align)
{
    // Get positions of ghost block cells
    std::vector<sf::Vector2i> tiles = getcellPositionForGhostBLock();

    for (sf::Vector2i item : tiles)
    {
        sf::RectangleShape rec(sf::Vector2f{float(cell_size - 1), float(cell_size - 1)});
        rec.setPosition(sf::Vector2f{float(item.y * cell_size + move_in_x + align), float(item.x * cell_size + move_in_y + align)});

        // Set transparent fill color and outline
        rec.setFillColor(sf::Color::Transparent);
        rec.setOutlineThickness(-2.0f);
        rec.setOutlineColor(outer_color[block_id]);

        window.draw(rec);
    }
}

std::vector<sf::Vector2i> Block::getCellPosition()
{
    // Calculate positions of active block cells
    std::vector<sf::Vector2i> tiles = block_cell[rotation_state];
    std::vector<sf::Vector2i> new_position;
    for (sf::Vector2i item : tiles)
    {
        sf::Vector2i temp = sf::Vector2i{item.x + row_offset, item.y + col_offset};
        new_position.push_back(temp);
    }
    return new_position;
}

std::vector<sf::Vector2i> Block::getcellPositionForGhostBLock()
{
    // Calculate positions of ghost block cells
    std::vector<sf::Vector2i> tiles = getCellPosition();
    std::vector<sf::Vector2i> new_position;
    for (sf::Vector2i item : tiles)
    {
        sf::Vector2i newPosition = sf::Vector2i(item.x + row_offset_ghost_block, item.y);
        new_position.push_back(newPosition);
    }
    return new_position;
}

void Block::moveBlock(int move_by_row, int move_by_col)
{
    // Update block position
    row_offset += move_by_row;
    col_offset += move_by_col;
}

void Block::rotate()
{
    // Rotate the block
    rotation_state++;
    if (rotation_state == static_cast<int>(block_cell.size()))
    {
        rotation_state = 0;
    }
}

void Block::undoRotation()
{
    // Undo the last rotation
    rotation_state--;
    if (rotation_state < 0)
    {
        rotation_state = static_cast<int>(block_cell.size()) - 1;
    }
}

void Block::moveGhostBlock(int move_by_rows)
{
    // Update ghost block position
    row_offset_ghost_block += move_by_rows;
}
