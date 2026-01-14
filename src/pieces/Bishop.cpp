#include "pieces/Bishop.h"
#include "Board.h"

Bishop::Bishop(Color color)
    : Piece(color)
{
    auto &texture = accessTexture();
    if (this->getColor() == Color::White)
    {
        if (!texture.loadFromFile("../assets/white_bishop.png"))
            throw std::runtime_error("Failed to load asset: white_bishop.png");
        texture.setSmooth(true);
    }
    else
    {
        if (!texture.loadFromFile("../assets/black_bishop.png"))
            throw std::runtime_error("Failed to load asset: black_bishop.png");
        texture.setSmooth(true);
    }
}

std::vector<Position> Bishop::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    // "Up-left"
    for (int r = from.row - 1, c = from.col - 1; r >= 0 && c >= 0; --r, --c)
    {
        Position to{r, c};
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

    // "Up-right"
    for (int r = from.row - 1, c = from.col + 1; r >= 0 && c < 8; --r, ++c)
    {
        Position to{r, c};
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

    // "Down-left"
    for (int r = from.row + 1, c = from.col - 1; r < 8 && c >= 0; ++r, --c)
    {
        Position to{r, c};
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

    // "Down-right"
    for (int r = from.row + 1, c = from.col + 1; r < 8 && c < 8; ++r, ++c)
    {
        Position to{r, c};
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
