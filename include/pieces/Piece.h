#pragma once
#include "Color.h"
#include "Position.h"
#include "Board.h"

class Piece
{
private:
	Color color;

public:
	explicit Piece(Color color);
	virtual ~Piece();

	Color getColor() const;

    virtual std::vector<Position> getPossibleMoves(
        const Board &board,
        const Position &from
    ) const = 0;
};
