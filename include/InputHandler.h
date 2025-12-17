#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"

class InputHandler
{
private:
    sf::RenderWindow &window;
    int tileSize;

    bool clickAvailable;
    Position clickedPosition;
public:
    InputHandler(sf::RenderWindow &window, int tileSize);

    void handleEvent(const sf::Event &event);
    bool hasClicked() const;
    Position getClickedPosition() const;
    void clearClick();
};
