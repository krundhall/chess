#pragma once
#include "pieces/Piece.h"

class Board
{
private:
	Piece* grid[8][8]{ nullptr };
public:
	Board();
	~Board();

	Piece* getPieceAt(int row, int col) const;
	void setPieceAt(int row, int col, Piece* piece);

	void addPiece(int row, int col, Color color);
};
