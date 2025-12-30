#include "pieces/Piece.h"

Piece::Piece(Color color, PieceType pieceType)
    : color(color), pieceType(pieceType)
{
}

Piece::~Piece()
{
}

Color Piece::getColor() const
{
	return this->color;
}

bool Piece::canMove(const Position &from, const Position &to, const Board &board) const
{
    return false;
}

PieceType Piece::getType() const
{
    return this->pieceType;
}

bool Piece::getHasMoved() const
{
    return this->hasMoved;
}

void Piece::setHasMoved(bool state)
{
    this->hasMoved = state;
}
