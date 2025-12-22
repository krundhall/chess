#pragma once
#include "Renderer.h"
#include "Position.h"
#include "Board.h"
#include "pieces/Pawn.h"
#include "InputHandler.h"

class Game
{
private:
    Board board;
    Renderer renderer;
    InputHandler input;

    Color currentTurn = Color::White;
    Piece* selectedPiece = nullptr;
    Position selectedPosition = {-1, -1};
public:
    Game();
    void run();

private:
    void setupBoard();
    void handleInput();
};
