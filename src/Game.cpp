#include "Game.h"
#include <iostream>
#include <algorithm>

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
    if (piece->getColor() != currentTurn)
        return false;

    // castling

    if (piece->getType() == PieceType::King &&
        std::abs(from.col - to.col) == 2)
    {
        return canCastle(from, to);
    }

    // check possible moves for piece
    auto pieceMoves = piece->getPossibleMoves(board, from);
    if (std::find(pieceMoves.begin(), pieceMoves.end(), to) == pieceMoves.end())
        return false;


    // king in check?


    return true;
}

bool Game::canCastle(const Position &from, const Position &to) const
{
    Piece* king = board.getPieceAt(from);

    if (!king || king->getType() != PieceType::King)
        return false;

    if (king->getHasMoved())
        return false;

    int colDiff = to.col - from.col; // should be either 2 or -2 depending on king or queenside
    bool kingSide = colDiff > 0; // more then 0 would be kingside/short/O-O
    int rookCol = kingSide ? 7 : 0; // ternary to decide what rook

    Piece* rook = board.getPieceAt({from.row, rookCol});
    if (!rook || rook->getType() != PieceType::Rook || rook->getHasMoved())
        return false;


    return true;
}

bool Game::leavesKingInCheck(const Position &from, const Position &to) const
{

    Piece* captured = board.getPieceAt(to);
    Piece* moving = board.getPieceAt(from);


    return false;
}

Position Game::locateKing(Color color) const
{
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col ++)
        {
            Piece* p = board.getPieceAt({row, col});
            if (p && p->getColor() == color && p->getType() == PieceType::King)
            {
                Position kingPos = {row, col};
                return kingPos;
            }
        }


    throw std::logic_error("King not found, you silly goose!");
}

bool Game::isKingInCheck(Color color) const
{
    Position kingPos = locateKing(color);

    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
        {
            Position from{row, col};
            Piece* piece = board.getPieceAt(from);

            if (!piece)
                continue;

            if (piece->getColor() == color)
                continue;

            auto moves = piece->getPossibleMoves(board, from);
            if (std::find(moves.begin(), moves.end(), kingPos) != moves.end())
                return true;
        }

    return false;
}
