#include <iostream>
#include "Source/Balltastic.h"
int main()
{
    Balltastic game;
    if (!game.init())
    {
        return -1;
    }

    game.run();
    std::cout << "Exiting Game!" << std::endl;
    return 0;
}