#include "Pattern.hh"

using namespace Core;

Pattern::Pattern(Team team, uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction) :
        lineLength(length), posOfFirst(posOfFirst), direction(direction)
{
    allocLine();
    line[0] = first;
    for (int i = 1; i < length - 1; ++i)
        line[i] = team;
    line[length - 1] = last;
}

Pattern::Pattern(Team team, boardPos_t pos) : lineLength(1), posOfFirst(pos)
{
    allocLine();
    line[0] = team;
    direction = 1;
}

Pattern::Pattern() : line(NULL)
{ }

Pattern::~Pattern()
{ }

bool Pattern::operator==(const Pattern & other)
{
    if (lineLength != other.lineLength || posOfFirst != other.posOfFirst || direction != other.direction)
        return (false);
    for (int i = 0; i < lineLength; ++i)
        if (line[i] != other.line[i])
            return (false);
    return (true);
}

void Pattern::set(uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction)
{
    Team team = getTeam();
    lineLength = length;
    reallocLine();
    this->posOfFirst = posOfFirst;
    this->direction = direction;
    line[0] = first;
    for (int i = 1; i < length - 1; ++i)
        line[i] = team;
    line[length - 1] = last;
}

void Pattern::breatAt(uint8_t posOnPattern)
{
    if (posOnPattern == 2)
    {
        lineLength = 1;
        line[0] = line[1];
        posOfFirst += direction;
    }
    else
    {
        line[posOnPattern] = NOPLAYER;
        lineLength = posOnPattern + (uint8_t)1;
    }
}

void Pattern::reallocLine()
{
    //TODO: preallocation (static array of 21 vectors)
    free(line);
    allocLine();
}

void Pattern::allocLine()
{
    //TODO: preallocation
    line = (Team *)malloc(lineLength);
}

Team Pattern::getTeam()
{
    return (line[lineLength > 1]);
}
