#pragma once
#include "Color.h"
#include "Position.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Board;

class Piece
{
private:
	Color color;
    bool hasMoved = false;
    sf::Texture texture;

public:
	explicit Piece(Color color);
	virtual ~Piece();

	Color getColor() const;

    virtual std::vector<Position> getPossibleMoves(const Board &board, const Position &from) const = 0;
    bool getHasMoved() const;
    void setHasMoved(bool state);

    sf::Texture& accessTexture();
};
