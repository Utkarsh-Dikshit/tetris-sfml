#include "header/block.h"

class LBlock : public Block
{
public:
    LBlock()
    {
        block_id = 1;
        block_cell[0] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
        block_cell[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
        block_cell[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
        block_cell[3] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};

class JBlock : public Block
{
public:
    JBlock()
    {
        block_id = 2;
        block_cell[0] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        block_cell[1] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
        block_cell[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
        block_cell[3] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
        moveBlock(0, 3);
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        block_id = 3;
        block_cell[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        block_cell[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
        block_cell[2] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
        block_cell[3] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        moveBlock(-1, 3);
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        block_id = 4;
        block_cell[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        moveBlock(0, 4);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        block_id = 5;
        block_cell[0] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        block_cell[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
        block_cell[2] = {{1, 1}, {1, 2}, {2, 0}, {2, 1}};
        block_cell[3] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        block_id = 6;
        block_cell[0] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
        block_cell[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 1}};
        block_cell[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
        block_cell[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
        moveBlock(0, 3);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        block_id = 7;
        block_cell[0] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        block_cell[1] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
        block_cell[2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
        block_cell[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
        moveBlock(0, 3);
    }
};