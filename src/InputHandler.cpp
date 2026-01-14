#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow &window, int tileSize)
    : window(window), tileSize(tileSize), clickAvailable(false), clickedPosition{0,0}
{}

void InputHandler::handleEvent(const sf::Event &event)
{
    if (event.type != sf::Event::MouseButtonPressed)
        return;

    if (event.mouseButton.button != sf::Mouse::Left)
        return;

    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    // TODO: creates problems when window is resized
    int col = x / tileSize;
    int row = y / tileSize;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;


    clickedPosition = Position{row, col};
    clickAvailable = true;
}

bool InputHandler::hasClicked() const
{
    return clickAvailable;
}

Position InputHandler::getClickedPosition() const
{
    return clickedPosition;
}

void InputHandler::clearClick()
{
    clickAvailable = false;
}
