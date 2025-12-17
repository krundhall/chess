#include "Board.h"

Board::Board()
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

Piece* Board::getPieceAt(int row, int col) const
{
	return this->grid[row][col];
}

void Board::setPieceAt(int row, int col, Piece* piece)
{
	grid[row][col] = piece;
}

void Board::addPiece(int row, int col, Color color)
{
	grid[row][col] = new Piece(color);
}
