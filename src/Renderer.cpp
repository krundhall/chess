#include "Renderer.h"
#include "Board.h"
#include "pieces/Piece.h"

#include <filesystem>
#include <iostream> //temp

Renderer::Renderer(unsigned int width, unsigned int height, const char* title)
	: window(sf::VideoMode(width, height), title), tileSize(100)
{
	window.setFramerateLimit(100);
    loadTextures();
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
				tile.setFillColor(sf::Color(89, 39, 92));
			tile.setPosition(j * tileSize, i * tileSize);
			window.draw(tile);
		}
}

void Renderer::drawPieces(const Board& board)
{
    sf::Sprite sprite;

	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
		{
			Piece* piece = board.getPieceAt(Position{row, col});
			if (piece == nullptr)
				continue;

            // build the key to call the sprite map
            auto key = std::make_pair(piece->getType(), piece->getColor());
            sprite.setTexture(textures[key]);

            // scale the texture accordingly to tileSize
            auto texSize = sprite.getTexture()->getSize();
            sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
            float scale = (tileSize * 0.65f) / texSize.x;
            sprite.setScale(scale, scale);

            sprite.setPosition(
            col * tileSize + tileSize / 2.f,
            row * tileSize + tileSize / 2.f
            );

            window.draw(sprite);
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

void Renderer::loadTextures()
{
    std::cout << "CWD: "
              << std::filesystem::current_path()
              << std::endl;

    if (!textures[{PieceType::Pawn, Color::White}].loadFromFile("../assets/white_pawn.png"))
        std::cout << "Failed to load white pawn\n";

    if (!textures[{PieceType::Pawn, Color::Black}].loadFromFile("../assets/black_pawn.png"))
        std::cout << "Failed to load black pawn\n";
}
