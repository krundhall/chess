#include "Board.h"
#include <iostream>

void Board::removePiece(int x, int y)
{
}

bool Board::isInsideBoard(int x, int y) const
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

Board::Board()
{
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
        {
            this->board[y][x] = nullptr;
        }
}

Board::~Board()
{
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            delete board[y][x];
}

Piece* Board::getPiece(int x, int y) const
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return nullptr;
    
    return board[y][x];
}

bool Board::placePiece(Piece *piece, int x, int y)
{

}

bool Board::movePiece(int fromX, int fromY, int toX, int toY)
{

    // Out of bounds
    if (!isInsideBoard(fromX, fromY) || !isInsideBoard(toX, toY))
        return false;

    // Piece trying to move
    Piece* piece = getPiece(fromX, fromY);
    if (!piece) // If piece doesnt exist on square we are trying to move from
        return false;
    
    // Check if piece is allowed to move
    if (!piece->canMove(*this, fromX, fromY, toX, toY))
        return false;

    // Check if piece and target is same color
    Piece* target = getPiece(toX, toY);
    if (target && target->getColor() == piece->getColor())
        return false;

    // On capture, remove target
    if (target)
        delete target;

    // Move Piece
    board[fromY][fromX] = nullptr;
    board[toY][toX] = piece;
    piece->moveTo(toX, toY);

    return true;
}

