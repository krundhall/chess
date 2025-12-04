#include <SFML/Graphics.hpp>
#include "BoardRenderer.h"
int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(800,800), "Chess");

    // run program as long as window is open
    while (window.isOpen())
    {
        // check all window's events that were triggered since last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // rendering
        window.clear(sf::Color::Black);

        
        
        window.display();
    }

    return 0;
}