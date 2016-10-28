#ifndef CORE_DEFINITIONS_HH_
#define CORE_DEFINITIONS_HH_

#include <stddef.h>
#include <iostream>

namespace Core
{
    enum GamePlayers : uint8_t
    {
        ONEPLAYER,
        TWOPLAYERS,
        TWOAIS
    };

    enum Team : uint8_t
    {
        WHITE,
        BLACK
    };

    typedef char GameBoard_t[19 * 19];
}

#endif