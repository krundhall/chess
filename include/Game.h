#pragma once
#include "Renderer.h"
#include "Position.h"
#include "Board.h"

class Game
{
private:
    Board board;
    Renderer renderer;

    Color currentTurn = Color::White;
    Piece* selectedPiece = nullptr;
    Position selectedPosition = {-1, -1};
public:
    Game();
    void run();

private:
    void setup();
    void handleInput();
};
