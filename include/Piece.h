#pragma once
#include "Position.h"
#include <string>
#include <vector>
using namespace std;

class Piece
{
private:
    enum class pieceType { King, Queen, Rook, Bishop, Knight, Pawn };
    enum class Color { White, Black };
    Position pos;
public:
    Piece();
    virtual ~Piece();

    pieceType getPieceType() const;
    Color getColor() const;
    Position getPos() const;
    void setPosition(const Position& newPos);

    virtual vector<Position> getPossibleMoves(const Board& board) const = 0;
    virtual Piece* clone() const = 0;
    virtual void move() = 0; // Varje subklass sköter sin egna move
    
};