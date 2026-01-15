#include "Game.h"
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "[FATAL ERROR]: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
