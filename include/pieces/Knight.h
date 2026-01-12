#pragma once
#include "pieces/Piece.h"

class Knight : public Piece
{
private:
public:
    Knight(Color color);

    std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const override;
};
