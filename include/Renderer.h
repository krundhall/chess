#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Renderer
{
private:
	sf::RenderWindow window;
	int tileSize = 100;

public:
	Renderer(unsigned int width, unsigned int height, const char* title);

	bool isOpen() const;
	void pollEvents();
	void clear();
	void display();
	void drawBoard();
	void drawPieces(const Board& board);

	sf::RenderWindow& getWindow();
};
