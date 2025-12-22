#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "InputHandler.h"

class Renderer
{
private:
	sf::RenderWindow window;
	int tileSize;

public:
	Renderer(unsigned int width, unsigned int height, const char* title);

	bool isOpen() const;
	void pollEvents(InputHandler &input);
	void clear();
	void display();
	void drawBoard();
	void drawPieces(const Board& board);

	sf::RenderWindow& getWindow();
    int getTileSize() const;
};
