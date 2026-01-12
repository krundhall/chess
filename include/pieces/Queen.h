#pragma once
#include "pieces/Piece.h"

class Queen : public Piece
{
private:
public:
    Queen(Color color);

    std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const override;

};
