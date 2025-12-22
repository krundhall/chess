#include "Game.h"
#include <iostream>

Game::Game()
    : renderer(800, 800, "Chess"), input(renderer.getWindow(), renderer.getTileSize())
{
    setupBoard();
}

void Game::run()
{
    while (renderer.isOpen())
    {
        renderer.pollEvents(input);

        handleInput();

        renderer.clear();

        renderer.drawBoard();
        renderer.drawPieces(board);

        renderer.display();
    }
}



void Game::setupBoard()
{
    board.setPieceAt({6,0}, new Pawn(Color::White));
}

void Game::handleInput()
{
    if (!input.hasClicked())
        return;

    Position clicked = input.getClickedPosition();

    if (!selectedPosition)
    {
        if (board.getPieceAt(clicked) != nullptr)
        {
            selectedPosition = clicked;
            std::cout << " -- 46 -- " << std::endl; //debug print
        }
    }
    else
    {
        movePiece(*selectedPosition, clicked);
        selectedPosition.reset();
        std::cout << " -- 53 -- " << std::endl; //debug print
    }

    input.clearClick();
}

void Game::movePiece(const Position &from, const Position &to)
{
    Piece* piece = board.getPieceAt(from);

    if (!piece)
        return;

    board.setPieceAt(to, piece);
    board.setPieceAt(from, nullptr);
}
