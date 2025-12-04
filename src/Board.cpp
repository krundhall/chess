#include "Board.h"
using namespace std;

Piece* Board::getPieceAt(const Position& pos) const
{
    return grid[pos.row][pos.col];
}

bool Board::setPieceAt(const Position& pos, Piece *p)
{
    grid[pos.row][pos.col] = p;
    if (p != nullptr)
        p->setPosition(pos);
    return true;
}

void Board::movePiece(const Position &from, const Position &to)
{
}

void Board::initialize()
{
}
