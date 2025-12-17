#include "Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, const char* title)
	: window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(100);
}

bool Renderer::isOpen() const
{
	return window.isOpen();
}

void Renderer::pollEvents(InputHandler &input)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

        input.handleEvent(event);
	}
}

void Renderer::clear()
{
	window.clear(sf::Color::Black);
}

void Renderer::display()
{
	window.display();
}

void Renderer::drawBoard()
{
	// light square = RGB(238,238,210)
	// dark square = RGB(118,150,86)
	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			if ((i + j) % 2 == 0)
				tile.setFillColor(sf::Color(238, 238, 210));
			else
				tile.setFillColor(sf::Color(118, 150, 86));
			tile.setPosition(j * tileSize, i * tileSize);
			window.draw(tile);
		}
}

void Renderer::drawPieces(const Board& board)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			Piece* piece = board.getPieceAt(Position{i, j});
			if (piece == nullptr)
				continue;

			sf::CircleShape circle(40);

			if (piece->getColor() == Color::White)
				circle.setFillColor(sf::Color(245, 245, 245));
			else
				circle.setFillColor(sf::Color(30, 30, 30));

			float x = j * tileSize + (tileSize / 2.0f - 40);
			float y = i * tileSize + (tileSize / 2.0f - 40);

			circle.setPosition(x, y);
			window.draw(circle);
		}
}

sf::RenderWindow& Renderer::getWindow()
{
	return window;
}

int Renderer::getTileSize() const
{
    return this->tileSize;
}
