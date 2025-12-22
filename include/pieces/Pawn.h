#pragma once
#include "pieces/Piece.h"
#include <vector>

class Pawn : public Piece
{
private:
    bool hasMoved;
public:
    explicit Pawn(Color color);

    std::vector<Position> getPossibleMoves(
        const Board &board,
        const Position &from
    ) const override;
};
