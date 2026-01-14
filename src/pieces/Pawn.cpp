#include "pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(Color color)
    : Piece(color)
{
    auto &texture = accessTexture();
    if (this->getColor() == Color::White)
    {
        if (!texture.loadFromFile("../assets/white_pawn.png"))
            throw std::runtime_error("Failed to load asset: white_pawn.png");
        texture.setSmooth(true);
    }
    else
    {
        if (!texture.loadFromFile("../assets/black_pawn.png"))
            throw std::runtime_error("Failed to load asset: black_pawn.png");
        texture.setSmooth(true);
    }
}

std::vector<Position> Pawn::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    if (this->getColor() == Color::White)
    {
        Position oneStep{from.row - 1, from.col};
        Position twoStep{from.row - 2, from.col};

        // two squares
        if (!this->getHasMoved())
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
            if (target && target->getColor() != this->getColor())
                possibleMoves.push_back(diagLeft);
        }

        // diagonal right
        Position diagRight{from.row - 1, from.col + 1};
        if (diagRight.row >= 0 && diagRight.col < 8)
        {
            Piece* target = board.getPieceAt(diagRight);
            if (target && target->getColor() != this->getColor())
                possibleMoves.push_back(diagRight);
        }

    }

    else // if color==color::black
    {
        Position oneStep{from.row + 1, from.col};
        Position twoStep{from.row + 2, from.col};

        // two squares
        if (!this->getHasMoved())
        {
            if (oneStep.row <= 7 &&
                twoStep.row <= 7 &&
                board.getPieceAt(oneStep) == nullptr &&
                board.getPieceAt(twoStep) == nullptr)
            {
                possibleMoves.push_back(twoStep);
            }
        }
        // one squares
        if (oneStep.row <= 7 &&
            board.getPieceAt(oneStep) == nullptr)
        {
            possibleMoves.push_back(oneStep);
        }

        // diagonal left (capture)
        Position diagLeft{from.row + 1, from.col - 1};
        if (diagLeft.row <= 7 && diagLeft.col >= 0)
        {
            Piece* target = board.getPieceAt(diagLeft);
            if (target && target->getColor() != this->getColor())
                possibleMoves.push_back(diagLeft);
        }
        // diagonal right
        Position diagRight{from.row + 1, from.col + 1};
        if (diagRight.row <= 7 && diagRight.col <= 7)
        {
            Piece* target = board.getPieceAt(diagRight);
            if (target && target->getColor() != this->getColor())
                possibleMoves.push_back(diagRight);
        }
    }

    return possibleMoves;
}
