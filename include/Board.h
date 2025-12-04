#pragma once
#include "Piece.h"
class Board
{
private:
    Piece* board[8][8];
    void removePiece(int x, int y);
    bool isInsideBoard(int x, int y) const;
    bool isKingInCheckAfterMove() const;
public:
    Board();
    ~Board();

    Piece* getPiece(int x, int y) const;
    bool placePiece(Piece* piece, int x, int y);
    bool movePiece(int fromX, int fromY, int toX, int toY);
};
