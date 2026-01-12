#pragma once
#include "pieces/Piece.h"

class King : public Piece
{
private:
public:
    King(Color color);

    std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const override;

};
