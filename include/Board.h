#pragma once
#include "pieces/Piece.h"
#include "Position.h"

class Board
{
private:
	Piece* grid[8][8]{ nullptr };
public:
	Board();
	~Board();

	Piece* getPieceAt(const Position &position) const;
	void setPieceAt(const Position &position, Piece* piece);

	void addPiece(const Position &position, Color color);
};
