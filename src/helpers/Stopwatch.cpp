//
// Stopwatch.cpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
//
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
//
// Started on  Mon Apr 18 16:11:08 2016 Esteban Lewis
// Last update Mon Apr 18 17:18:37 2016 Esteban Lewis
//

#include <Helpers/Stopwatch.hh>

Stopwatch::Stopwatch()
{ }

Stopwatch::~Stopwatch()
{ }

void
Stopwatch::set()
{
    gettimeofday(&startTime, NULL);
}

long
Stopwatch::elapsedMs()
{
    struct timeval checkTime;

    gettimeofday(&checkTime, NULL);
    return ((checkTime.tv_sec - startTime.tv_sec) * 1000 +
            (checkTime.tv_usec - startTime.tv_usec) / 1000);
}

long Stopwatch::elapsedUs() {
    struct timeval checkTime;

    gettimeofday(&checkTime, NULL);
    return ((checkTime.tv_sec - startTime.tv_sec) * 1000000 +
            (checkTime.tv_usec - startTime.tv_usec));
}
