#pragma once
#include "pieces/Piece.h"

class Bishop : public Piece
{
private:
public:
    Bishop(Color color);

    std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const override;

};
