#pragma once

enum class Color
{
	White,
	Black
};

class Piece
{
private:
	Color color;

public:
	explicit Piece(Color color);
	virtual ~Piece();

	Color getColor() const;

};