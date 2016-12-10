//
// Created by celeriy on 28/10/16.
//

#include <Graph.hpp>
#include "Core.hh"
#include "CoreOberser.hh"
#include "Helpers/rotatingVector.hpp"
#include "Helpers/Stopwatch.hh"

#undef main

class mytest
{
public:
    mytest() { }
    mytest(int i) : i(i) { }
    mytest(const mytest & other) : i(other.i) { }
    mytest &operator=(const mytest & other)
    {
        this->i = other.i;
        return (*this);
    }
    int i;
};

int main(int ac, char **av)
{
/*
    rotatingVector<int> arr;

    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(8);

    for (auto it : arr)
    {
        std::cout << it << std::endl;
    }

    auto it = arr.begin();
    ++it;
    while (it != arr.end())
    {
        it = arr.erase(it);
        std::cout << std::endl;
        for (auto it : arr)
        {
            std::cout << it << std::endl;
        }
    }
*/


    Core::Core core;

    return (0);
}
