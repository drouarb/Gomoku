#ifndef CORE_DEFINITIONS_HPP_
#define CORE_DEFINITIONS_HPP_

#include <stddef.h>
#include <iostream>
#include <map>

#define XBOARD 19
#define BOARDSIZE (XBOARD * XBOARD)

#define TEAMOF(i)(i == 0 ? WHITE : BLACK)
#define TEAMNAME(team)(team == WHITE ? "White" : "Black")

#define MC_EXPLORATION 1

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
    DOUBLE_THREE = 0x00,
    BREAKABLE_FIVE = 0x01,
    TIME_10MS = 0x02,
    TIME_20MS = 0x03,
    TIME_50MS = 0x04
};

static const std::map<RuleID, std::string> RuleToString = {
        {DOUBLE_THREE, "Double three"},
        {BREAKABLE_FIVE, "Breakable Five"},
        {TIME_10MS, "Timed AI: 10 ms"},
        {TIME_20MS, "Timed AI: 20 ms"},
        {TIME_50MS, "Timed AI: 50 ms"}
};

typedef char* GameBoard_t;
typedef int16_t boardPos_t;
typedef int32_t weight_t;

inline Team	operator!(Team team)
{
  if (team == Team::WHITE)
    return (Team::BLACK);
  else if (team == Team::BLACK)
    return (Team::WHITE);
  return (Team::NOPLAYER);
}

#endif
