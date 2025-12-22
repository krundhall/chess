#include "Game.h"
#include <iostream> //tabort
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

        if (input.hasClicked())
    {
        Position pos = input.getClickedPosition();
        std::cout << pos.row << ", " << pos.col << "\n";

        input.clearClick();
    }

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
}
