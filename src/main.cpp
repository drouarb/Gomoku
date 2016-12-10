//
// Created by celeriy on 28/10/16.
//

#include <Graph.hpp>
#include "Core.hh"
#include "CoreOberser.hh"
#include "Helpers/rotatingArray.hpp"

#undef main

int main(int ac, char **av)
{
    rotatingArray<int, 4> arr;

    arr.push_back(2);
    arr.push_back(4);

    for (auto it : arr)
    {
        std::cout << it << std::endl;
    }

    //Core::Core core;

    return (0);
}