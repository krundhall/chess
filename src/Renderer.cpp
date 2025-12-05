#include "Renderer.h"

void Renderer::draw(sf::RenderWindow &window, const Board &board)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));

            if ((x+y) % 2 == 0)
                square.setFillColor(sf::Color(240, 217, 181));
            else
                square.setFillColor(sf::Color(181, 136, 99));
            
            square.setPosition(x * tileSize, y * tileSize);
            window.draw(square);

            Piece* p = board.getPiece(x, y);
            if (p)
            {
                // draw sprite
            }
        }
    }
}