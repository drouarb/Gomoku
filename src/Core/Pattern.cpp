#include "Pattern.hh"

using namespace Core;

Pattern::Pattern(Team team, uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction) :
        lineLength(length), posOfFirst(posOfFirst), direction(direction)
{
    //allocLine();
    line[0] = first;
    for (int i = 1; i < length - 1; ++i)
        line[i] = team;
    line[length - 1] = last;
}

Pattern::Pattern(Team team, boardPos_t pos) : lineLength(1), posOfFirst(pos)
{
    //allocLine();
    line[0] = team;
    direction = 1;
}

Pattern::Pattern(const Pattern & other) : lineLength(other.lineLength), posOfFirst(other.posOfFirst), direction(other.direction)
{
    //allocLine();
    for (int i = 0; i < lineLength; ++i)
        line[i] = other.line[i];
}

Pattern::Pattern()// : line(NULL)
{ }

Pattern::~Pattern()
{
/*
    if (line)
        freeLine();
*/
}

bool Pattern::operator==(const Pattern & other)
{
    if (lineLength == 1 && (other.lineLength == 1 && other.line[0] == line[0]))
        return (true);
    if (lineLength != other.lineLength || posOfFirst != other.posOfFirst || direction != other.direction)
        return (false);
    for (int i = 0; i < lineLength; ++i)
        if (line[i] != other.line[i])
            return (false);
    return (true);
}

Pattern & Pattern::operator=(const Pattern &other)
{
/*
    if (line)
        freeLine();
*/
    lineLength = other.lineLength;
    posOfFirst = other.posOfFirst;
    direction = other.direction;
    //allocLine();
    for (int i = 0; i < lineLength; ++i)
        line[i] = other.line[i];
    return (*this);
}

void Pattern::set(uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction)
{
    Team team = getTeam();
    //freeLine();
    lineLength = length;
    //allocLine();
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

Team Pattern::getTeam()
{
    return (line[lineLength > 1]);
}

/*

void Pattern::freeLine()
{
    //free(line);
    (this->*delLineFunArr[lineLength])();
}

void Pattern::allocLine()
{
    //line = (Team *)malloc(lineLength);
    (this->*createLineFunArr[lineLength])();
}

*/
/*
 * Line reservation lists.
 *//*


reservList<Pattern::line_s<1>> Pattern::line1Stock = reservList<Pattern::line_s<1>>(1024);
reservList<Pattern::line_s<4>> Pattern::line2Stock = reservList<Pattern::line_s<4>>(1024);
reservList<Pattern::line_s<5>> Pattern::line3Stock = reservList<Pattern::line_s<5>>(1024);
reservList<Pattern::line_s<6>> Pattern::line4Stock = reservList<Pattern::line_s<6>>(1024);
reservList<Pattern::line_s<7>> Pattern::line5Stock = reservList<Pattern::line_s<7>>(1024);
reservList<Pattern::line_s<12>> Pattern::line10Stock = reservList<Pattern::line_s<12>>(256);
reservList<Pattern::line_s<21>> Pattern::line19Stock = reservList<Pattern::line_s<21>>(128);

*/
/*
 * Line creation.
 *//*


void Pattern::createLine1()
{
    line = reinterpret_cast<Team*>(line1Stock.take());
}

void Pattern::createLine2()
{
    line = reinterpret_cast<Team*>(line2Stock.take());
}

void Pattern::createLine3()
{
    line = reinterpret_cast<Team*>(line3Stock.take());
}

void Pattern::createLine4()
{
    line = reinterpret_cast<Team*>(line4Stock.take());
}

void Pattern::createLine5()
{
    line = reinterpret_cast<Team*>(line5Stock.take());
}

void Pattern::createLine6to10()
{
    line = reinterpret_cast<Team*>(line10Stock.take());
}

void Pattern::createLine11to19()
{
    line = reinterpret_cast<Team*>(line19Stock.take());
}

const Pattern::createLineFun Pattern::createLineFunArr[22] = {
        NULL,
        &Pattern::createLine1,
        NULL,
        NULL,
        &Pattern::createLine2,
        &Pattern::createLine3,
        &Pattern::createLine4,
        &Pattern::createLine5,
        &Pattern::createLine6to10,
        &Pattern::createLine6to10,
        &Pattern::createLine6to10,
        &Pattern::createLine6to10,
        &Pattern::createLine6to10,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19,
        &Pattern::createLine11to19
};

*/
/*
 * Line destruction.
 *//*


void Pattern::delLine1()
{
    line1Stock.giveBack(reinterpret_cast<line_s<1>*>(line));
}

void Pattern::delLine2()
{
    line2Stock.giveBack(reinterpret_cast<line_s<4>*>(line));
}

void Pattern::delLine3()
{
    line3Stock.giveBack(reinterpret_cast<line_s<5>*>(line));
}

void Pattern::delLine4()
{
    line4Stock.giveBack(reinterpret_cast<line_s<6>*>(line));
}

void Pattern::delLine5()
{
    line5Stock.giveBack(reinterpret_cast<line_s<7>*>(line));
}

void Pattern::delLine6to10()
{
    line10Stock.giveBack(reinterpret_cast<line_s<12>*>(line));
}

void Pattern::delLine11to19()
{
    line19Stock.giveBack(reinterpret_cast<line_s<21>*>(line));
}

const Pattern::delLineFun Pattern::delLineFunArr[22] = {
        NULL,
        &Pattern::delLine1,
        NULL,
        NULL,
        &Pattern::delLine2,
        &Pattern::delLine3,
        &Pattern::delLine4,
        &Pattern::delLine5,
        &Pattern::delLine6to10,
        &Pattern::delLine6to10,
        &Pattern::delLine6to10,
        &Pattern::delLine6to10,
        &Pattern::delLine6to10,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19,
        &Pattern::delLine11to19
};
*/
