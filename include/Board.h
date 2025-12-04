#pragma once
#include "Piece.h"
using namespace std;

class Board
{
private:
    Piece* grid[8][8];
public:
    Piece* getPieceAt(const Position& pos) const;
    bool setPieceAt(const Position& pos, Piece* p);
    void movePiece(const Position& from, const Position& to);
    void initialize();
};