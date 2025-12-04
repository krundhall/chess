#include <SFML/Graphics.hpp>

int main()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(640,480), "First window!");

    // create a shape
    sf::CircleShape player(20.f); //radius 50
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f); // ish center

    // gameloop
    while (window.isOpen())
    {
        // event handling
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // input (arrow keys)
        float speed = 2.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-speed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(speed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0.f, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0.f, speed);
        

        // rendering
        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}