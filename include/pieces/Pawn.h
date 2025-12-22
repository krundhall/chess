#pragma once
#include "pieces/Piece.h"
#include <vector>

class Pawn : public Piece
{
public:
    explicit Pawn(Color color);

    std::vector<Position> getPossibleMoves(
        const Board &board,
        const Position &from
    ) const override;
};
