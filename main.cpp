#include <iostream>

#include "Source/SMALL_RTS.h"

int main()
{
    SMALL_RTS game;
    if (!game.init())
    {
        return -1;
    }

    game.run();
    std::cout << "Exiting Game!" << std::endl;
    return 0;
}