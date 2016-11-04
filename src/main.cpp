//
// Created by celeriy on 28/10/16.
//

#include "Core.hh"
#include "PatternManager.hh"

int main(int ac, char **av)
{
    //Core::Core core;
    Core::PatternManager pm;

    std::cout << pm << std::endl;
    pm.addStone(15, BLACK);
    std::cout << pm << std::endl;
    pm.addStone(245, WHITE);
    std::cout << pm << std::endl;
    pm.removeStone(15);
    std::cout << pm << std::endl;

    return (0);
}