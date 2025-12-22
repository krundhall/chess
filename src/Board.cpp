#include "Board.h"
#include "pieces/Piece.h"
#include <iostream>
Board::Board()
    : grid{}
{
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			delete grid[i][j];
			grid[i][j] = nullptr;
		}
}

Piece* Board::getPieceAt(const Position &position) const
{
	return this->grid[position.row][position.col];
}

void Board::setPieceAt(const Position &position, Piece* piece)
{
	grid[position.row][position.col] = piece;
}
