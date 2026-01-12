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
    for (int i = 0; i < 8; i++)
    {
        board.setPieceAt({6,i}, new Pawn(Color::White));
        board.setPieceAt({1,i}, new Pawn(Color::Black));
    }

    board.setPieceAt({7,0}, new Rook(Color::White));
    board.setPieceAt({7,7}, new Rook(Color::White));
    board.setPieceAt({0,0}, new Rook(Color::Black));
    board.setPieceAt({0,7}, new Rook(Color::Black));

    board.setPieceAt({7,1}, new Knight(Color::White));
    board.setPieceAt({7,6}, new Knight(Color::White));
    board.setPieceAt({0,1}, new Knight(Color::Black));
    board.setPieceAt({0,6}, new Knight(Color::Black));

    board.setPieceAt({7,2}, new Bishop(Color::White));
    board.setPieceAt({7,5}, new Bishop(Color::White));
    board.setPieceAt({0,2}, new Bishop(Color::Black));
    board.setPieceAt({0,5}, new Bishop(Color::Black));

    board.setPieceAt({7,4}, new King(Color::White));
    board.setPieceAt({0,4}, new King(Color::Black));

    board.setPieceAt({7,3}, new Queen(Color::White));
    board.setPieceAt({0,3}, new Queen(Color::Black));



}

void Game::handleInput()
{
    if (!input.hasClicked())
        return;

    Position clicked = input.getClickedPosition();

    if (!selectedPosition)
    {
        Piece* p = board.getPieceAt(clicked);
        if (p && p->getColor() == currentTurn)
        {
            selectedPosition = clicked;
            std::cout << "[SELECT] "
                      << colorToStr(p->getColor())
                      << " at (" << clicked.row << "," << clicked.col << ")\n";
        }
    }

    else
    {
        Position from = *selectedPosition;

        if (clicked == from)
        {
            std::cout << "[CANCEL] clicked same square\n";
            selectedPosition.reset();
        }
        else
        {
            std::cout << "[TRY MOVE] from ("
                      << from.row << "," << from.col
                      << ") to ("
                      << clicked.row << "," << clicked.col << ")\n";


            if (isValidMove(from, clicked))
            {
                std::cout << "[MOVE OK]\n";
                movePiece(from, clicked);

                currentTurn = (currentTurn == Color::White) ? Color::Black : Color::White;
                std::cout << "[TURN] "
                          << (currentTurn == Color::White ? "WHITE" : "BLACK")
                          << "\n";
            }
            else
            {
                std::cout << "[MOVE INVALID]\n";
            }

            selectedPosition.reset();
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
    if (target)
        delete target;

    board.setPieceAt(to, piece);
    board.setPieceAt(from, nullptr);

    piece->setHasMoved(true);
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

    if (from == to)
        return false;

    if (!piece)
        return false;

    if (target && target->getColor() == piece->getColor())
        return false;

    // piece rules
    auto moves = piece->getPossibleMoves(board, from);
    if (std::find(moves.begin(), moves.end(), to) == moves.end())
        return false;

    // leavesKingInCheck / castle / en passant

    return true;
}

bool Game::canCastle(const Position &from, const Position &to) const
{
    Piece* king = board.getPieceAt(from);

    if (!king || dynamic_cast<King*>(king) == nullptr)
        return false;

    if (king->getHasMoved())
        return false;

    int colDiff = to.col - from.col; // should be either 2 or -2 depending on king or queenside
    bool kingSide = colDiff > 0; // more then 0 would be kingside/short/O-O
    int rookCol = kingSide ? 7 : 0; // ternary to decide what rook

    Piece* rook = board.getPieceAt({from.row, rookCol});
    if (!rook || dynamic_cast<Rook*>(rook) || rook->getHasMoved())
        return false;


    return true;
}

bool Game::leavesKingInCheck(const Position &from, const Position &to)
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
            if (p && p->getColor() == color && dynamic_cast<King*>(p) != nullptr)
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

const char* Game::colorToStr(Color c)
{
    return (c == Color::White) ? "WHITE" : "BLACK";
}
