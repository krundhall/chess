#include "Game.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

static std::string posToAlg(const Position &p)
{
    char file = 'a' + p.col;
    char rank = '8' - p.row;
    return std::string{file, rank};
}

static void recordMove(const std::string &path, const Position &from, const Position &to, bool capture)
{
    std::ofstream file(path, std::ios::app);
    if (!file)
        return;
    if (capture)
        file << posToAlg(from) << " x " << posToAlg(to) << '\n';
    else
        file << posToAlg(from) << " " << posToAlg(to) << '\n';
}

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
    // trunc, cleans file when new game
    std::ofstream file("moves.txt", std::ios::trunc);
    (void)file;

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
    if (gameOver)
        return;

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
                std::cout << "[TURN] " << (currentTurn == Color::White ? "WHITE" : "BLACK") << "\n";

                if (isCheckmate(currentTurn))
                {
                    std::cout << "[GAME OVER] Checkmate! " << (currentTurn == Color::White ? "WHITE" : "BLACK") << " is checkmated.\n";
                    gameOver = true;
                }
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
    bool wasCapture = (target != nullptr);
    if (target)
        delete target;

    // castling logic
    if (dynamic_cast<King*>(piece) != nullptr && from.row == to.row && std::abs(to.col - from.col) == 2)
    {
        int dc = to.col - from.col;
        int rookCol = (dc > 0) ? 7 : 0;
        int rookDestCol = from.col + (dc > 0 ? 1 : -1);

        Piece* rook = board.getPieceAt({from.row, rookCol});

        board.setPieceAt(to, piece);
        board.setPieceAt(from, nullptr);

        if (rook)
        {
            board.setPieceAt({from.row, rookDestCol}, rook);
            board.setPieceAt({from.row, rookCol}, nullptr);
            rook->setHasMoved(true);
        }

        piece->setHasMoved(true);

        recordMove("moves.txt", from, to, wasCapture);

        return;
    }

    board.setPieceAt(to, piece);
    board.setPieceAt(from, nullptr);

    piece->setHasMoved(true);

    recordMove("moves.txt", from, to, wasCapture);
}

bool Game::isValidMove(const Position &from, const Position &to)
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
    {
        bool isKing = dynamic_cast<King*>(piece) != nullptr;
        bool isTwoColMove = std::abs(to.col - from.col) == 2;

        if (!(isKing && isTwoColMove && canCastle(from, to)))
            return false;
    }

    // leavesKingInCheck
    if (leavesKingInCheck(from, to))
        return false;

    return true;
}

bool Game::canCastle(const Position &from, const Position &to)
{
    Piece* king = board.getPieceAt(from);
    if (!king || dynamic_cast<King*>(king) == nullptr || king->getHasMoved())
        return false;

    // must move exactly two squares
    int dc = to.col - from.col;
    if (dc != 2 && dc != -2)
        return false;


    int rookCol = (dc > 0) ? 7 : 0;
    Piece* rook = board.getPieceAt({from.row, rookCol});
    if (!rook || dynamic_cast<Rook*>(rook) == nullptr || rook->getColor() != king->getColor() || rook->getHasMoved())
        return false;

    // clear path?
    int step = (rookCol > from.col) ? 1 : -1;
    for (int c = from.col + step; c != rookCol; c += step)
        if (board.getPieceAt({from.row, c}) != nullptr)
            return false;

    if (isKingInCheck(king->getColor()))
        return false;


    Position mid{from.row, from.col + (dc / 2)}; // +1 or -1
    if (leavesKingInCheck(from, mid) || leavesKingInCheck(from, to))
        return false;

    return true;
}

bool Game::leavesKingInCheck(const Position &from, const Position &to)
{

    Piece* targetSquare = board.getPieceAt(to);
    Piece* piece = board.getPieceAt(from);

    if (!targetSquare && !piece)
        return false;

    board.setPieceAt(to, piece);
    board.setPieceAt(from, nullptr);
    bool inCheck = isKingInCheck(piece->getColor());
    board.setPieceAt(from, piece);
    board.setPieceAt(to, targetSquare);

    return inCheck;
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

bool Game::isCheckmate(Color color)
{
    if (!isKingInCheck(color))
        return false;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Position from{r, c};
            Piece* p = board.getPieceAt(from);
            if (!p || p->getColor() != color)
                continue;

            auto moves = p->getPossibleMoves(board, from);
            for (const Position &to : moves)
            {
                if (isValidMove(from, to))
                    return false; // found a legal move
            }
        }
    }
    return true;
}
