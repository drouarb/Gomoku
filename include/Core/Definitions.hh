#ifndef CORE_DEFINITIONS_HH_
#define CORE_DEFINITIONS_HH_

#include <stddef.h>
#include <iostream>

#define XBOARD 19
#define BOARDSIZE (XBOARD * XBOARD)

#define TEAMOF(i)(i == 0 ? WHITE : BLACK)
#define TEAMNAME(team)(team == WHITE ? "White" : "Black")

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

enum RuleID : uint8_t
{
    DOUBLE_THREE,
    BREAKABLE_FIVE,
    TIME_10MS,
    TIME_20MS,
    TIME_50MS
};

typedef char* GameBoard_t;
typedef int16_t boardPos_t;

#endif
