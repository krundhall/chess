#pragma once
#include "pieces/Piece.h"

class Rook : public Piece
{
private:
public:
    Rook(Color color);

    std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const override;
};
