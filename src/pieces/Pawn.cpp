#include "pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(Color color)
    : Piece(color)
{
    this->hasMoved = false;
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

bool Pawn::canMove(const Position &from, const Position &to, const Board &board) const
{
    if (this->color == Color::White)
    {
        // One step
        if (to.col == from.col &&
            to.row == from.row - 1 &&
            board.getPieceAt(to) == nullptr)
            return true;

        // Two step
        if (!hasMoved &&
            to.col == from.col &&
            to.row == from.row - 2 &&
            board.getPieceAt(to) == nullptr)
            return true;

        // Diagonal Capture
        if (to.row == from.row - 1 &&
            (to.col == from.col - 1 || to.col == from.col + 1))
            {
                Piece* target = board.getPieceAt(to);
                if (target && target->getColor() != this->color)
                    return true;
            }
    }
    else //this->color == Color::Black
    {

    }

    return true;
}
