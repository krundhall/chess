#include "pieces/King.h"
#include "Board.h"

King::King(Color color)
    : Piece(color)
{
    auto &texture = accessTexture();
    if (this->getColor() == Color::White)
    {
        if (!texture.loadFromFile("../assets/white_king.png"))
            throw std::runtime_error("Failed to load asset: white_king.png");
        texture.setSmooth(true);
    }
    else
    {
        if (!texture.loadFromFile("../assets/black_king.png"))
            throw std::runtime_error("Failed to load asset: black_king.png");
        texture.setSmooth(true);
    }
}

std::vector<Position> King::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int i = 0; i < 8; ++i)
    {
        int r = from.row + dr[i];
        int c = from.col + dc[i];

        if (r < 0 || r >= 8 || c < 0 || c >= 8)
            continue;

        Position to{r,c};
        Piece* target = board.getPieceAt(to);

        if (target == nullptr || target->getColor() != this->getColor())
            possibleMoves.push_back(to);
    }

    return possibleMoves;
}
