#include "pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(Color color)
    : Piece(color, PieceType::Pawn)
{
}

PieceType Pawn::getType() const
{
    return PieceType::Pawn;
}

std::vector<Position> Pawn::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    if (this->color == Color::White)
    {
        Position oneStep{from.row - 1, from.col};
        Position twoStep{from.row - 2, from.col};

        // two squares
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

        // one squares
        if (oneStep.row >= 0 &&
            board.getPieceAt(oneStep) == nullptr)
        {
            possibleMoves.push_back(oneStep);
        }

        // diagonal left
        Position diagLeft{from.row -1, from.col - 1};
        if (diagLeft.row >= 0 && diagLeft.col >= 0)
        {
            Piece* target = board.getPieceAt(diagLeft);
            if (target && target->getColor() != color)
                possibleMoves.push_back(diagLeft);
        }

        // diagonal right
        Position diagRight{from.row - 1, from.col + 1};
        if (diagRight.row >= 0 && diagRight.col < 8)
        {
            Piece* target = board.getPieceAt(diagRight);
            if (target && target->getColor() != color)
                possibleMoves.push_back(diagRight);
        }

    }

    return possibleMoves;
}
