#include "Game.h"
#include "Renderer.h"
#include "pieces/Piece.h"
#include "Board.h"
#include "InputHandler.h"
#include <iostream>

int main()
{
	Renderer renderer(800, 800, "SFML WINDOW");
	Board board;
    InputHandler input(renderer.getWindow(), renderer.getTileSize());

    board.addPiece(Position{0, 0}, Color::White);
    board.addPiece(Position{7,7}, Color::Black);

	while (renderer.isOpen())
	{
        renderer.pollEvents(input);

        if (input.hasClicked())
        {
            Position p = input.getClickedPosition();
            std::cout << "Clicked: row =" << p.row << " col=" << p.col << '\n';
            input.clearClick();
        }

        renderer.clear();
        renderer.drawBoard();
        renderer.drawPieces(board);
        renderer.display();
	}

	return 0;
}
