#include "Board.h"
#include <iostream>
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

Piece* Board::getPieceAt(const Position &position) const
{
	return this->grid[position.row][position.col];
}

void Board::setPieceAt(const Position &position, Piece* piece)
{
	grid[position.row][position.col] = piece;
}

void Board::addPiece(const Position &position, Color color)
{
    if (getPieceAt(position) != nullptr)
    {
        std::cerr << "ERROR: addPiece could not add the piece. Piece already exists on that square" << std::endl;
        return;
    }

	grid[position.row][position.col] = new Piece(color);
}
