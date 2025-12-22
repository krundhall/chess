#include "pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(Color color)
    : color(color)
{
}

std::vector<Position> Pawn::getPossibleMoves(const Board &board, const Position &from) const
{
    return std::vector<Position>();
}
