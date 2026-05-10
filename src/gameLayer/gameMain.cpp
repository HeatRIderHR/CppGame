#include <raylib.h>
#include "gameMain.h"
#include <iostream>
bool initGame()
{

    return true;
}

bool updateGame()
{
    DrawRectangle(50, 50, 100, 200, {255, 0, 0, 255});
    return true;
}

void closeGame()
{
    std::cout << "Fin" << std::endl;
}