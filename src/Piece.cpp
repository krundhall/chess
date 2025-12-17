#include "pieces/Piece.h"

Piece::Piece(Color color)
{
	this->color = color;
}

Piece::~Piece()
{
}

Color Piece::getColor() const
{
	return this->color;
}
