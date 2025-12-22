#pragma once
#include "Color.h"
#include "Position.h"
#include <vector>

class Board;

class Piece
{
protected:
	Color color;

public:
	explicit Piece(Color color);
	virtual ~Piece();

	Color getColor() const;

    virtual std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const = 0;
};
