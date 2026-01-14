#include "pieces/Queen.h"
#include "Board.h"

Queen::Queen(Color color)
    : Piece(color)
{
    auto &texture = accessTexture();
    if (this->getColor() == Color::White)
    {
        if (!texture.loadFromFile("../assets/white_queen.png"))
            throw std::runtime_error("Failed to load asset: white_queen.png");
        texture.setSmooth(true);
    }
    else
    {
        if (!texture.loadFromFile("../assets/black_queen.png"))
            throw std::runtime_error("Failed to load asset: black_queen.png");
        texture.setSmooth(true);
    }
}

std::vector<Position> Queen::getPossibleMoves(const Board &board, const Position &from) const
{
    std::vector<Position> possibleMoves;

    const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int i = 0; i < 8; ++i)
    {
        int r = from.row + dr[i];
        int c = from.col + dc[i];

        while (r >= 0 && r < 8 && c >= 0 && c < 8)
        {
            Position to{r,c};
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

            r += dr[i];
            c += dc[i];


        }
    }

    return possibleMoves;
}
