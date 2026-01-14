#pragma once
#include "Renderer.h"
#include "Position.h"
#include "Board.h"
#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"
#include "pieces/Knight.h"
#include "pieces/Piece.h"

#include "InputHandler.h"
#include <optional>
class Game
{
private:
    Board board;
    Renderer renderer;
    InputHandler input;

    Color currentTurn = Color::White;
    std::optional<Position> selectedPosition;
    bool gameOver = false;
public:
    Game();
    void run();

private:
    void setupBoard();
    void handleInput();
    void movePiece(const Position &from, const Position &to);
    bool isValidMove(const Position &from, const Position &to);
    bool canCastle(const Position &from, const Position &to);
    bool leavesKingInCheck(const Position &from, const Position &to);
    bool isCheckmate(Color color);
    Position locateKing(Color color) const;
    bool isKingInCheck(Color color) const;
    static const char* colorToStr(Color c);

};
