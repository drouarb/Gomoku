#include "PatternManager.hh"

using namespace Core;

PatternManager::PatternManager()
{ }

PatternManager::PatternManager(PatternManager & other) : patterns(other.getPatterns()), map(other.getMap())
{ }

PatternManager::~PatternManager()
{ }

PLIST<PatternRef>& PatternManager::operator[](boardPos_t pos)
{
  return (map[pos]);
}

PLIST<Pattern>& PatternManager::getPatterns()
{
    return (patterns);
}

const PLIST<Pattern>& PatternManager::getPatterns() const
{
    return (patterns);
}

PMAP<boardPos_t, PLIST<PatternRef> > PatternManager::getMap() const
{
    return (map);
}

void PatternManager::addStone(boardPos_t position, Team team)
{
    bool done[9] = { false, false, false, false, false, false, false, false, false };
    bool found = false;
    for (int i = 0; i <= 8; i++)
    {
        if (!done[i] && map.find(position + checkMap[i]) != map.end())
        {
            auto list = map[position + checkMap[i]];
            //size remembrance and prev_it are needed because the iterator can be erased
            uint8_t size;
            PLIST<PatternRef>::iterator prev_it = list.end();
            PLIST<PatternRef>::iterator it = list.begin();
            while (it != list.end())
            {
                size = (uint8_t)list.size();
                auto & pattern = *it;


                    if (pattern.pattern->line[pattern.posOnPattern] != team)
                    {
                        if (pattern.pattern->line[pattern.posOnPattern] == NOPLAYER)
                        {
                            if (i == 0)
                            {
                                found = true;
                                pattern.pattern->line[pattern.posOnPattern] = team;
                            }
                            //found value is extremity of a pattern OR in case of checkMap[0], value may be middle of a pattern
                            //this if statement is always true for i == 0
                            //TODO: interrupted pattern
                            //found=true if applicable
                        }
                        //else: nothing
                    }
                    else
                    {
                        found = true;

                        Pattern *newpattern = NULL;
                        boardPos_t newlen;
                        if (pattern.pattern->lineLength == 1)
                        {
                            std::cout << "found 1 i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                            //single stone
                            newlen = 4;
                            removeFromMap(pattern.pattern);
                        }
                        else if (pattern.pattern->team == team && pattern.pattern->direction == checkMap[ACTDIR(i)])
                        {
                            std::cout << "found aligned i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                            //aligned pattern
                            newlen = pattern.pattern->lineLength + (boardPos_t) 1;
                            removeFromMap(pattern.pattern);
                            //TODO: interrupted pattern...?
                        }
                        else
                        {
                            std::cout << "found non-aligned i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                            //new pattern
                            patterns.push_front(Pattern(team, 4, teamAt(position + checkMap[i] * (boardPos_t) 2),
                                                        teamAt(position + checkMap[OPPDIR(i)]),
                                                        position + checkMap[i] * (boardPos_t) 2,
                                                        checkMap[ACTDIR(i)]));
                            newpattern = &patterns.front();
                            newlen = 4;
                        }

                        if (i <= 4) //TODO: make sure patterns can't have a direction above 4!
                        {
                            //check other side
                            for (auto &oppPattern : map[position + checkMap[OPPDIR(i)]])
                                if (oppPattern.pattern->line[oppPattern.posOnPattern] != team)
                                {
                                    //found value is extremity of a oppPattern
                                    //this if statement is always true for i == 0
                                    //TODO: interrupted oppPattern
                                    //set done if applicable
                                }
                                else
                                {
                                    done[OPPDIR(i)] = true;
                                    if (oppPattern.pattern->lineLength == 1)
                                    {
                                        std::cout << "found opp 1 i=" << std::to_string(OPPDIR(i)) << " pos=" << std::to_string(position + checkMap[OPPDIR(i)]) << std::endl;
                                        //single stone
                                        newlen += 1;
                                        removePattern(oppPattern.pattern);
                                    }
                                    else if (pattern.pattern->team == team && oppPattern.pattern->direction == checkMap[ACTDIR(i)])
                                    {
                                        std::cout << "found opp aligned i=" << std::to_string(OPPDIR(i)) << " pos=" << std::to_string(position + checkMap[OPPDIR(i)]) << std::endl;
                                        //aligned oppPattern
                                        newlen += oppPattern.pattern->lineLength - 2;
                                        removePattern(oppPattern.pattern);
                                        //TODO: interrupted...?
                                    }
                                    else
                                    {
                                        std::cout << "found opp non-aligned i=" << std::to_string(OPPDIR(i)) << " pos=" << std::to_string(position + checkMap[OPPDIR(i)]) << std::endl;
                                        //found stone is part of a pattern, but not an entire pattern
                                        newlen += 1;
                                    }
                                    break;
                                }
                        }

                        //change pattern or newpattern to give it the new length and extremities
                        Pattern *target = (newpattern ? newpattern : pattern.pattern);
                        boardPos_t firstPos;
                        Team firstTeam;
                        boardPos_t dir = (i > 4 ? checkMap[i] : checkMap[OPPDIR(i)]);
                        if (i <= 4)
                        {
                            firstPos = target->posOfFirst;
                            if (target->lineLength == 1)
                                firstPos += checkMap[i];
                        }
                        else
                        {
                            firstPos = position + checkMap[OPPDIR(i)];
                        }
                        firstTeam = teamAt(firstPos);

                        target->set(newlen, firstTeam, teamAt(firstPos + (newlen - 1) * checkMap[OPPDIR(i)]), firstPos, dir);
                        checkExtremities(target);
                        addToMap(target);
                    }

                if (list.size() != size)
                {
                    if (prev_it == list.end())
                    {
                        it = list.begin();
                    }
                    else
                    {
                        it = prev_it;
                        ++it;
                    }
                }
                else
                {
                    prev_it = it;
                    ++it;
                }
            }
        }
    }
    if (!found)
    {
        std::cout << "create new 1-stone pattern" << std::endl;
        patterns.push_front(Pattern(team, position));
        map[position].push_front(PatternRef());
        map[position].front().posOnPattern = 0;
        map[position].front().pattern = &patterns.front();
    }

    std::cout << *this << std::endl;
}

void PatternManager::removeStone(boardPos_t position)
{
    if (map.find(position) != map.end())
    {
        Team team;

        auto list = map[position];
        //size remembrance and prev_it are needed because the iterator can be erased
        uint8_t size;
        PLIST<PatternRef>::iterator prev_it = list.end();
        PLIST<PatternRef>::iterator it = list.begin();
        while (it != list.end())
        {
            size = (uint8_t)list.size();
            auto & pattern = *it;

            team = pattern.pattern->team;
            if (pattern.pattern->line[pattern.posOnPattern] != team)
            {
                //removed extremity of line (not interrupted, since interruption is always empty value)
                pattern.pattern->line[pattern.posOnPattern] = NOPLAYER;
                //TODO: this might create an interrupted pattern!
            }
            else
            {
                std::cout << "pattern: start=" << std::to_string(pattern.pattern->posOfFirst) << " len=" << std::to_string(pattern.pattern->lineLength) << " dir=" << std::to_string(pattern.pattern->direction) << std::endl;

                removeFromMap(pattern.pattern);
                //TODO: if pattern len >= 6 and not interrupted: becomes interrupted
                if (pattern.pattern->lineLength == 1)
                {
                    removeFromList(pattern.pattern);
                }
                else
                {
                    //TODO: change or erase interrupted

                    //full size of the second half, including extremity, excluding the position of the removed stone
                    uint8_t halfSize = pattern.pattern->lineLength - pattern.posOnPattern - (uint8_t)1;
                    if (halfSize >= 2)
                    {
                        //second half of pattern: create new pattern
                        if (halfSize == 2)
                        {
                            //1 stone left
                            PLIST<PatternRef> & singleStoneList = map[position + pattern.pattern->direction];
                            if (singleStoneList.end() == singleStoneList.begin())
                            {
                                //if stone is not part of any other pattern, create new 1-stone pattern
                                std::cout << "2nd half: 1 stone" << std::endl;
                                patterns.push_front(Pattern(team, position + pattern.pattern->direction));
                                addToMap(&patterns.front());
                            }
                        }
                        else
                        {
                            //new multiple-stone pattern (starting at position, since pattern dir is always positive)
                            std::cout << "2nd half: multiple stones" << std::endl;
                            patterns.push_front(Pattern(team, halfSize + (uint8_t) 1, NOPLAYER,
                                                        pattern.pattern->line[pattern.pattern->lineLength -
                                                                              (uint8_t) 1],
                                                        position, pattern.pattern->direction));
                            addToMap(&patterns.front());
                        }
                    }
                    //else: no second half to create

                    //first half of pattern
                    halfSize = pattern.posOnPattern;
                    if (halfSize >= 2)
                    {
                        if (halfSize == 2)
                        {
                            PLIST<PatternRef> & singleStoneList = map[position - pattern.pattern->direction];
                            if (singleStoneList.begin() != singleStoneList.end())
                            {
                                //only one stone, and it is part of another pattern
                                std::cout << "1st half: erased" << std::endl;
                                removeFromList(pattern.pattern);
                            }
                            else
                            {
                                //change pattern
                                std::cout << "1st half: change pattern" << std::endl;
                                pattern.pattern->breatAt(pattern.posOnPattern);
                                addToMap(pattern.pattern);
                            }
                        }
                        else
                        {
                            //change pattern
                            std::cout << "1st half: change pattern" << std::endl;
                            pattern.pattern->breatAt(pattern.posOnPattern);
                            addToMap(pattern.pattern);
                        }
                    }
                    else
                    {
                        //destroy pattern
                        std::cout << "1st half: erased" << std::endl;
                        removeFromList(pattern.pattern);
                    }
                }
            }

            if (list.size() < size)
            {
                if (prev_it != list.end())
                {
                    it = list.begin();
                }
                else
                {
                    it = prev_it;
                    ++it;
                }
            }
            else
            {
                prev_it = it;
                ++it;
            }
        }
    }
    std::cout << *this << std::endl;
}

void PatternManager::removePattern(Pattern * pattern)
{
    //remove pattern from map entries
    removeFromMap(pattern);
    
    //remove from pattern list
    removeFromList(pattern);
}

void PatternManager::removeFromList(Pattern * pattern)
{
    for (PLIST<Pattern>::iterator it = patterns.begin(); it != patterns.end(); ++it)
        if (&*it == pattern)
        {
            patterns.erase(it);
            break;
        }
}

void PatternManager::removeFromMap(Pattern *pattern)
{
    boardPos_t max = pattern->posOfFirst + pattern->lineLength * pattern->direction;
    for (boardPos_t pos = pattern->posOfFirst; pos < max; pos += pattern->direction)
    {
        for (PLIST<PatternRef>::iterator it = map[pos].begin(); it != map[pos].end(); ++it)
            if (it->pattern == pattern)
            {
                map[pos].erase(it);
                break;
            }
        if (map[pos].size() == 0)
            map.erase(pos);
    }
}

Team PatternManager::teamAt(boardPos_t pos)
{
    if (map.find(pos) == map.end() || map[pos].size() == 0) //TODO: there are empty entries!
        return (NOPLAYER);
    PatternRef & pr = map[pos].front();
    return (pr.pattern->line[pr.posOnPattern]);
}

void PatternManager::addToMap(Pattern *pattern)
{
    uint8_t posOnPattern = 0;
    boardPos_t max = pattern->posOfFirst + pattern->lineLength * pattern->direction;
    for (boardPos_t pos = pattern->posOfFirst; pos < max; pos += pattern->direction)
    {
        addToMap(pattern, pos, posOnPattern);
        posOnPattern += 1;
    }
}

void PatternManager::addToMap(Pattern * pattern, boardPos_t position, uint8_t posOnPattern)
{
    map[position].push_front(PatternRef());
    map[position].front().pattern = pattern;
    map[position].front().posOnPattern = posOnPattern;
}

void PatternManager::checkExtremities(Pattern * pattern)
{
    //if extremities of pattern are also on a 1-stone pattern, remove that 1-stone pattern
    if (pattern->line[0] != pattern->team && pattern->line[0] != NOPLAYER)
    {
        removeOneStone(pattern->posOfFirst);
    }
    if (pattern->line[pattern->lineLength - 1] != pattern->team && pattern->line[pattern->lineLength - 1] != NOPLAYER)
    {
        removeOneStone(pattern->posOfFirst + (pattern->lineLength - (boardPos_t)1) * pattern->direction);
    }
}

void PatternManager::removeOneStone(boardPos_t position)
{
    for (auto pat = map[position].begin(); pat != map[position].end(); ++pat)
    {
        if (pat->pattern->lineLength == 1)
        {
            map[position].erase(pat);
            removeFromList(pat->pattern);
            break;
        }
    }
}




const boardPos_t PatternManager::checkMap[] = {
        0,
        -1,
        -XBOARD - 1,
        -XBOARD - 0,
        -XBOARD + 1,
        +1,
        +XBOARD + 1,
        +XBOARD - 0,
        +XBOARD - 1,
        -1, //back to start of list => no need for %
        -XBOARD - 1,
        -XBOARD - 0,
        -XBOARD + 1
};


const boardPos_t PatternManager::twoDistCircle[] = {
        0,
        -2,
        -2 * XBOARD - 2,
        -2 * XBOARD - 0,
        -2 * XBOARD + 2,
        +2,
        +2 * XBOARD + 2,
        +2 * XBOARD - 0,
        +2 * XBOARD - 2
};



std::ostream &operator<<(std::ostream & out, const Core::PatternManager & pm)
{
    out << "-- PATTERNS" << std::endl;
    for (auto& pattern : pm.getPatterns())
    {
        out << (void*)&pattern;
        out << " length=" << std::to_string((int)pattern.lineLength);
        if (pattern.interrupted)
            out << " interrupted";
        out << " startPos=" << pattern.posOfFirst;
        out << " dir=" << std::to_string((int)pattern.direction);
        out << " line=";
        for (int i = 0; i < pattern.lineLength; ++i)
            out << std::to_string((int)pattern.line[i]);
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
