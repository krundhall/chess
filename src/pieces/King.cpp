#include "pieces/King.h"

King::King(Color color)
    : Piece(color, PieceType::King), hasMoved(false)
{
}
