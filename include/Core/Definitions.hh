#ifndef CORE_DEFINITIONS_HH_
#define CORE_DEFINITIONS_HH_

#include <stddef.h>
#include <iostream>

#define XBOARD 19
#define BOARDSIZE (XBOARD * XBOARD)

#define TEAMOF(i)(i == 0 ? WHITE : BLACK)
#define TEAMNAME(team)(team == WHITE ? "White stones" : "Black stones")

enum GamePlayers : uint8_t
{
    ONEPLAYER,
    TWOPLAYERS,
    TWOAIS
};

enum Team : uint8_t
{
    NOPLAYER  = 0x00,
    WHITE     = 0x01,
    BLACK     = 0x02
};

typedef char* GameBoard_t;

#endif
