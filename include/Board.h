#pragma once
#include "Position.h"
class Piece;

class Board
{
private:
	Piece* grid[8][8]{ nullptr };
public:
	Board();
	~Board();

	Piece* getPieceAt(const Position &position) const;
	void setPieceAt(const Position &position, Piece* piece);
};
