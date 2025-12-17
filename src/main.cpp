#include "Game.h"
#include "Renderer.h"
#include "pieces/Piece.h"
#include "Board.h"

#include <iostream>

int main()
{
	Renderer renderer(800, 800, "SFML WINDOW");
	Board board;

    board.addPiece(Position{0, 0}, Color::White);
    board.addPiece(Position{7,7}, Color::Black);

	while (renderer.isOpen())
	{
		renderer.pollEvents();
		renderer.clear();
		renderer.drawBoard();
		renderer.drawPieces(board);
		renderer.display();
	}

	return 0;
}
