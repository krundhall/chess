#pragma once
#include "Color.h"
#include "Position.h"
#include <vector>

class Board;

enum class PieceType
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

class Piece
{
protected:
	Color color;

public:
	explicit Piece(Color color);
	virtual ~Piece();

	Color getColor() const;

    virtual PieceType getType() const = 0;
    virtual std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const = 0;
    virtual bool canMove(const Position &from, const Position &to, const Board &board) const;
};
