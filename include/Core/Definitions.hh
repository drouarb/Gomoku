#ifndef CORE_DEFINITIONS_HH_
#define CORE_DEFINITIONS_HH_

#include <stddef.h>
#include <iostream>

#define BOARDSIZE 19*19
#define XBOARD 19

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
      NOPLAYER = 0x00,
      WHITE = 0x01,
      BLACK = 0x02
    };

    typedef char* GameBoard_t;
}

#endif
