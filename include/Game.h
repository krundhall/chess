#pragma once
#include "Renderer.h"
#include "Position.h"
#include "Board.h"
#include "pieces/Pawn.h"
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
public:
    Game();
    void run();

private:
    void setupBoard();
    void handleInput();
    void movePiece(const Position &from, const Position &to);
};
