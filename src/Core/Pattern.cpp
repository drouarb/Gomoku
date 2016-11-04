#include "Pattern.hh"

using namespace Core;

Pattern::Pattern(Team team, uint8_t length, Team first, Team last) : lineLength(length), interrupted(0)
{
    line[0] = first;
    for (int i = 1; i < length - 1; ++i)
        line[i] = team;
    line[length - 1] = last;
}

Pattern::Pattern(Team team, uint8_t length, uint8_t interruptionIndex, Team first, Team last) : lineLength(length), interrupted(interruptionIndex != 0)
{
    line[0] = first;
    for (int i = 1; i < length - 1; ++i)
        line[i] = team;
    line[length - 1] = last;
    if (interrupted)
        line[interruptionIndex] = NOPLAYER;
}

Pattern::Pattern(Team team) : lineLength(1), interrupted(0)
{
    line[0] = team;
}

Pattern::~Pattern()
{ }

bool Pattern::operator==(const Pattern & other)
{
    if (lineLength != other.lineLength || interrupted != other.interrupted)
        return (false);
    for (int i = 0; i < lineLength; ++i)
        if (line[i] != other.line[i])
            return (false);
    return (true);
}
