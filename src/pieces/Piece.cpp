#include "pieces/Piece.h"

Piece::Piece(Color color)
    : color(color)
{
}

Piece::~Piece()
{
}

Color Piece::getColor() const
{
	return this->color;
}

bool Piece::getHasMoved() const
{
    return this->hasMoved;
}

void Piece::setHasMoved(bool state)
{
    this->hasMoved = state;
}

sf::Texture &Piece::accessTexture()
{
    return texture;
}
