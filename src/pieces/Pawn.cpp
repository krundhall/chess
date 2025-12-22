#include "pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(Color color)
    : Piece(color)
{
    this->hasMoved = false;
}

std::vector<Position> Pawn::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    if (this->color == Color::White)
    {
        Position oneStep{from.row - 1, from.col};
        Position twoStep{from.row - 2, from.col};

        // check if can move two squares
        if (!hasMoved)
        {
            if (oneStep.row >= 0 &&
                twoStep.row >= 0 &&
                board.getPieceAt(oneStep) == nullptr &&
                board.getPieceAt(twoStep) == nullptr)
            {
                possibleMoves.push_back(twoStep);
            }
        }

        // check one square ahead
        if (oneStep.row >= 0 &&
            board.getPieceAt(oneStep) == nullptr)
        {
            possibleMoves.push_back(oneStep);
        }

    }

    return possibleMoves;
}
