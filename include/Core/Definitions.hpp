#ifndef CORE_DEFINITIONS_HPP_
#define CORE_DEFINITIONS_HPP_

#include <stddef.h>
#include <iostream>
#include <map>

#define XBOARD 19
#define BOARDSIZE (XBOARD * XBOARD)

#define TEAMOF(i)(i == 0 ? WHITE : BLACK)
#define TEAMNAME(team)(team == WHITE ? "White" : "Black")

#define OPPTEAM(t)(t == BLACK ? WHITE : BLACK)

#define MC_EXPLORATION 3
#define SIM_RAND 3

#define THREADS_POOL 4

enum GamePlayers : int_fast8_t
{
    ONEPLAYER,
    TWOPLAYERS,
    TWOAIS
};

enum Team : int_fast8_t
{
    BORDER    = -0x01,
    NOPLAYER  =  0x00,
    WHITE     =  0x01,
    BLACK     =  0x02
};

enum RuleID : int_fast8_t
{
    DOUBLE_THREE = 0x00,
    BREAKABLE_FIVE = 0x01,
    TIME_10MS = 0x02,
    TIME_20MS = 0x03,
    TIME_50MS = 0x04,
    TIME_200MS = 0x05,
    TIME_1S = 0x06,
    TIME_3S = 0x07
};

static const std::map<RuleID, std::string> RuleToString = {
        {DOUBLE_THREE, "Double three"},
        {BREAKABLE_FIVE, "Breakable Five"},
        {TIME_10MS, "Timed AI: 10 ms"},
        {TIME_20MS, "Timed AI: 20 ms"},
        {TIME_50MS, "Timed AI: 50 ms"},
        {TIME_200MS, "Timed AI: 200 ms"},
        {TIME_1S, "Timed AI: 1 sec"},
        {TIME_3S, "Timed AI: 3 sec"}
};

typedef Team * GameBoard_t;
typedef int_fast32_t boardPos_t;
typedef int_fast32_t weight_t;

inline Team	operator!(Team team)
{
  if (team == Team::WHITE)
    return (Team::BLACK);
  else if (team == Team::BLACK)
    return (Team::WHITE);
  return (team);
}

#endif
