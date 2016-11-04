#include "PatternManager.hh"

using namespace Core;

PatternManager::PatternManager()
{ }

PatternManager::PatternManager(const PatternManager & other) : patterns(other.getPatterns()), map(other.getMap())
{ }

PatternManager::~PatternManager()
{ }

const PLIST<PatternRef>& PatternManager::operator[](boardPos_t pos) const
{
    return (map.at(pos));
}

const PLIST<Pattern>& PatternManager::getPatterns() const
{
    return (patterns);
}

const PMAP<boardPos_t, PLIST<PatternRef> > PatternManager::getMap() const
{
    return (map);
}

void PatternManager::addStone(uint16_t position, Team team)
{
    for (int i = 0; i < 9; i++)
    {
        /*
        for (auto& pattern : map[position + checkMap[i]]) // the [] operator creates an entry
        {
            // create/remove patterns
        }*/
    }

    // TEST
    patterns.push_front(Pattern(team));
    map[position].push_back({ &patterns.front(), 0 });
}

void PatternManager::removeStone(uint16_t position)
{
    /*for (auto& pattern : map[position]) // operator [] creates an entry
    {
        // create/remove patterns
    }*/

    // TEST
    patterns.remove(*map[position].front().pattern);
    map.erase(position);
}

void PatternManager::addPattern()
{
    //adds a pattern
}

void PatternManager::removePattern()
{
    //removes a pattern. If pattern is not used by the map anymore, remove it from the pattern list.
}



const boardPos_t PatternManager::checkMap[] = {
        0,
        -XBOARD - 1,
        -XBOARD - 0,
        -XBOARD + 1,
        +1,
        +XBOARD + 1,
        +XBOARD - 0,
        +XBOARD - 1,
        -1
};

std::ostream &operator<<(std::ostream & out, const Core::PatternManager & pm)
{
    out << "-- PATTERNS" << std::endl;
    for (auto& pattern : pm.getPatterns())
    {
        out << (void*)&pattern;
        int nbstones = pattern.lineLength;
        if (nbstones != 1)
            nbstones -= 2 - pattern.interrupted;
        out << " " << nbstones << " stones";
        if (pattern.interrupted)
            out << " interrupted";
        out << std::endl;
    }
    out << "-- MAP" << std::endl;
    for (auto entry : pm.getMap())
    {
        out << entry.first;
        for (auto pattern : entry.second)
        {
            out << " " << (void*)pattern.pattern << "-" << std::to_string(pattern.posOnPattern);
        }
        out << std::endl;
    }
    return out;
}