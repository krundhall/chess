#pragma once
#include "pieces/Piece.h"
#include <vector>

class Pawn : public Piece
{
private:
public:
    explicit Pawn(Color color);

    PieceType getType() const override;
    std::vector<Position> getPossibleMoves(
        const Board &board,
        const Position &from
    ) const override;
};
