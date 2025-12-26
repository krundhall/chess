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
        if (clicked == *selectedPosition)
        {
            std::cout << "Tried to move to the same square" << std::endl;
            selectedPosition.reset();
        }
        else
        {
            movePiece(*selectedPosition, clicked);
            selectedPosition.reset();
            std::cout << " -- 53 -- " << std::endl; //debug print
        }
    }

    input.clearClick();
}

void Game::movePiece(const Position &from, const Position &to)
{
    Piece* piece = board.getPieceAt(from);
    if (!piece)
        return;

    Piece* target = board.getPieceAt(to);
    if (target && target->getColor() == piece->getColor())
        return;

    board.setPieceAt(to, piece);
    board.setPieceAt(from, nullptr);
}

bool Game::isValidMove(const Position &from, const Position &to) const
{
    Piece* piece = board.getPieceAt(from);
    Piece* target = board.getPieceAt(to);

    // out of bounds check
    if (from.row < 0 || from.row > 7 ||
        from.col < 0 || from.col > 7 ||
        to.row   < 0 || to.row   > 7 ||
        to.col   < 0 || to.col   > 7)
        {
            return false;
        }

    // from != to
    if (from == to)
        return false;

    // from piece exists
    if (piece == nullptr)
        return false;

    // same color capture
    if (target && target->getColor() == piece->getColor())
        return false;

    // whos turn is it
    if (board.getPieceAt(from)->getColor() != currentTurn)
        return false;

    // piece canmove

    // special drag

    // king in check?

    return true;
}
