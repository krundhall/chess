#include "pieces/Rook.h"
#include "Board.h"

Rook::Rook(Color color)
    : Piece(color)
{
    auto &texture = accessTexture();
    if (this->getColor() == Color::White)
    {
        if (!texture.loadFromFile("../assets/white_rook.png"))
            throw std::runtime_error("Failed to load asset: white_rook.png");
        texture.setSmooth(true);
    }
    else
    {
        if (!texture.loadFromFile("../assets/black_rook.png"))
            throw std::runtime_error("Failed to load asset: black_rook.png");
        texture.setSmooth(true);
    }
}

std::vector<Position> Rook::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    // "Up"

    for (int r = from.row - 1; r >= 0; --r)
    {
        Position to{r, from.col};
        Piece* target = board.getPieceAt(to);

        if (target == nullptr)
        {
            possibleMoves.push_back(to);
        }
        else
        {
            if (target->getColor() != this->getColor())
                possibleMoves.push_back(to); // capture
            break;
        }
    }

    // "Down"

    for (int r = from.row + 1; r < 8; ++r)
    {
        Position to{r, from.col};
        Piece* target = board.getPieceAt(to);

        if (target == nullptr)
        {
            possibleMoves.push_back(to);
        }
        else
        {
            if (target->getColor() != this->getColor())
                possibleMoves.push_back(to); // capture
            break;
        }
    }

    // "Left"

    for (int c = from.col - 1; c >= 0; --c)
    {
        Position to{from.row, c};
        Piece* target = board.getPieceAt(to);

        if (target == nullptr)
        {
            possibleMoves.push_back(to);
        }
        else
        {
            if (target->getColor() != this->getColor())
                possibleMoves.push_back(to);
            break;
        }
    }

    // "Right"

    for (int c = from.col + 1; c < 8; ++c)
    {
        Position to{from.row, c};
        Piece* target = board.getPieceAt(to);

        if (target == nullptr)
        {
            possibleMoves.push_back(to);
        }
        else
        {
            if (target->getColor() != this->getColor())
                possibleMoves.push_back(to);
            break;
        }
    }

    return possibleMoves;
}
