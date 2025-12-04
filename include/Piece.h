#pragma once
using namespace std;


class Piece
{
public:
    enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King };
    enum Color { White, Black };

    Piece(Color color, PieceType type, int x, int y);
    virtual ~Piece() = default;

    virtual bool canMove(const Board& board, int fromX, int fromY, int toX, int toY) const = 0;
    void moveTo(int newX, int newY);

    int getX() const;
    int getY() const;
    Color getColor() const;
    PieceType getType() const;

protected:
    Color color;
    PieceType type;
    int x;
    int y;
};