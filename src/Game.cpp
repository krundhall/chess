#include "Game.h"

Game::Game()
    : renderer(800, 800, "Chess")
{
    setup();
}

void Game::run()
{
    board.setPieceAt({1,0}, new Pawn(Color::Black));
    board.setPieceAt({7,6}, new Pawn(Color::White));
}

void Game::setup()
{
}

void Game::handleInput()
{
}
