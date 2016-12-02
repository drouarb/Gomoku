#include "PatternManager.hh"

using namespace Core;

PatternRef::PatternRef()
{ }

PatternRef::~PatternRef()
{ }

PatternRef::PatternRef(Pattern * pat, uint8_t pos) : pattern(pat), posOnPattern(pos)
{ }

PatternManager::PatternManager() : map(), patterns()
{
    board = reinterpret_cast<GameBoard_t>(boardRl.take());
    //board = new char[XPBOARD * XPBOARD];
    for (int i = 0; i < XPBOARD * XPBOARD; ++i)
        board[i] = NOPLAYER;
}

PatternManager::PatternManager(const PatternManager & other) : patterns(other.getPatterns())
{
    board = reinterpret_cast<GameBoard_t>(boardRl.take());
    //board = new char[XPBOARD * XPBOARD];
    for (int i = 0; i < XPBOARD * XPBOARD; ++i)
        board[i] = other.board[i];
    for (Pattern & pattern : patterns)
        addToMap(&pattern);
}

PatternManager::~PatternManager()
{
    boardRl.giveBack(reinterpret_cast<line_s*>(board));
    //delete board;
}

PatternManager & PatternManager::operator=(const PatternManager & other)
{
    boardRl.giveBack(reinterpret_cast<line_s*>(board));
    board = reinterpret_cast<GameBoard_t>(boardRl.take());
    for (int i = 0; i < XPBOARD * XPBOARD; ++i)
        board[i] = other.board[i];
    patterns = other.patterns;
    map.clear();
    for (Pattern & pattern : patterns)
        addToMap(&pattern);
    return (*this);
}

bool PatternManager::operator==(const PatternManager & other)
{
    if (patterns.size() != other.patterns.size())
        return (false);
    for (auto it : patterns)
    {
        bool ok = false;
        for (auto it_oth : other.patterns)
            if (it == it_oth)
            {
                ok = true;
                break;
            }
        if (!ok)
            return (false);
    }
    return (true);
}

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

const PMAP<boardPos_t, PLIST<PatternRef> > & PatternManager::getMap() const
{
    return (map);
}

const PLIST<PatternRef> * PatternManager::patternsAt(boardPos_t pos) const
{
    try
    {
        return (&map.at(pos));
    }
    catch (std::out_of_range)
    {
        return (NULL);
    }
}

boardPos_t PatternManager::getPPos(boardPos_t x, boardPos_t y)
{
    return (y * (boardPos_t)XPBOARD + x + (boardPos_t)PBOARDDIFF);
}

void PatternManager::addStone(boardPos_t position, Team team)
{
  //std::cout << "addStone " << std::to_string(position) <<  " " << std::to_string(team) << std::endl;

    board[position] = team;

    bool done[9] = { false, false, false, false, false, false, false, false, false };
    bool found = false;
    int newpatterns = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (!done[i] && map.find(position + checkMap[i]) != map.end())
        {
            bool aligned = false;
            PatternRef * pattern = NULL;
            for (auto pref : map[position + checkMap[i]])
            {
                if (pref.pattern->line[pref.posOnPattern] == team)
                {
                    if (pref.pattern->lineLength == 1)
                    {
                        //1-stone pattern: only pattern
                        pattern = &pref;
                        break;
                    }
                    else if (isAligned(pref, i))
                    {
                        //found aligned
                        pattern = &pref;
                        aligned = true;
                        break;
                    }
                    else
                    {
                        //non-aligned: keep looking for aligned
                        pattern = &pref;
                    }
                }
            }
            if (pattern)
            {
                done[i] = true;
                found = true;

                Pattern *newpattern = NULL;
                boardPos_t newlen;
                if (pattern->pattern->lineLength == 1)
                {
		  //std::cout << "found 1 i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                    //single stone
                    newlen = 4;
                    removeFromMap(pattern->pattern);
                }
                else if (aligned)
                {
		  //std::cout << "found aligned i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                    //aligned pattern
                    newlen = pattern->pattern->lineLength + (boardPos_t) 1;
                    removeFromMap(pattern->pattern);
                }
                else
                {
		  //std::cout << "found non-aligned i=" << std::to_string(i) << " pos=" << std::to_string(position + checkMap[i]) << std::endl;
                    //new pattern
                    newpatterns++;
                    patterns.push_front(Pattern(team, 4, teamAt(position + checkMap[i] * (boardPos_t) 2),
                                                teamAt(position + checkMap[OPPDIR(i)]),
                                                position + checkMap[i] * (boardPos_t) 2,
                                                checkMap[ACTDIR(i)]));
                    newpattern = &patterns.front();
                    newlen = 4;
                }

                doOppPattern(position, i, team, *pattern, newlen, done);

                //change pattern or newpattern to give it the new length and extremities
                Pattern *target = (newpattern ? newpattern : pattern->pattern);

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

                target->set(newlen, firstTeam, teamAt(firstPos + (newlen - (boardPos_t)1) * dir), firstPos, dir);
                removeOSExtremities(target);

                //new patterns are added to the map afterwards
                if (!newpattern)
                    addToMap(target);
            }
        }
    }
    if (!addMiddle(position, team))
    {
        if (!found)
        {
	  //std::cout << "create new 1-stone pattern" << std::endl;
            patterns.push_front(Pattern(team, position));
            map[position].push_front(PatternRef(&patterns.front(), 0));
        }
    }

    //add new patterns to map
    auto it = patterns.begin();
    for (int i = 0; i < newpatterns; ++i)
    {
        addToMap(&*it);
        ++it;
    }

    //std::cout << *this << std::endl;
}

bool PatternManager::addMiddle(boardPos_t position, Team team)
{
    if (map.find(position) != map.end()) //TODO: optimize
    {
        for (auto pref : map[position])
        {
            pref.pattern->line[pref.posOnPattern] = team;
        }
        return (true);
    }
    return (false);
}

void PatternManager::doOppPattern(boardPos_t position, int i, Team team, PatternRef &pattern, boardPos_t &newlen, bool *done)
{
    if (i > 4)
        return;
    i = OPPDIR(i);
    if (done[i])
        return;

    //check other side
    bool aligned = false;
    PatternRef * foundOppPattern = NULL;
    //try to find an aligned one before taking a non-aligned one
    for (auto &oppPattern : map[position + checkMap[i]])
    {
        if (oppPattern.pattern->line[oppPattern.posOnPattern] == team)
        {
            if (oppPattern.pattern->lineLength == 1)
            {
                //1-stone pattern: only pattern
                foundOppPattern = &oppPattern;
                break;
            }
            else if (isAligned(oppPattern, i))
            {
                //found aligned
                foundOppPattern = &oppPattern;
                aligned = true;
                break;
            }
            else
            {
                //non-aligned: keep looking for aligned
                foundOppPattern = &oppPattern;
            }
        }
    }
    if (foundOppPattern)
    {
        done[i] = true;
        if (foundOppPattern->pattern->lineLength == 1)
        {
	  //std::cout << "found opp 1 i=" << std::to_string(i) << " pos="
	  //<< std::to_string(position + checkMap[i]) << std::endl;
            //single stone
            newlen += 1;
            removePattern(foundOppPattern->pattern);
        }
        else if (aligned)
        {
	  //std::cout << "found opp aligned i=" << std::to_string(i) << " pos="
	  //          << std::to_string(position + checkMap[i]) << std::endl;
            //aligned oppPattern
            newlen += foundOppPattern->pattern->lineLength - 2;
            removePattern(foundOppPattern->pattern);
        }
        else
        {
	  //std::cout << "found opp non-aligned i=" << std::to_string(i) << " pos="
	  //          << std::to_string(position + checkMap[i]) << std::endl;
            //found stone is part of a pattern, but not an entire pattern
            newlen += 1;
        }
    }
}

/**
 * Here we assume that:
 * - pref is located on one of the 8 places around the stone being added
 * - the pattern is of the same team
 * - the pattern is not a 1-stone pattern
 */
bool PatternManager::isAligned(PatternRef & pref, int dir)
{
    return (pref.pattern->line[pref.posOnPattern] == pref.pattern->getTeam() && pref.pattern->direction == checkMap[ACTDIR(dir)]);
}

void PatternManager::removeStone(boardPos_t position)
{
  //std::cout << "removeStone " << std::to_string(position) << std::endl;

    board[position] = NOPLAYER;

    if (map.find(position) != map.end())
    {
        Team team;

        auto list = map[position];
        //size remembrance and prev_it are needed because the iterator can be erased
        //uint8_t size;
        //PLIST<PatternRef>::iterator prev_it = list.end();
        PLIST<PatternRef>::iterator it = list.begin();
        while (it != list.end())
        {
            bool it_set = false;
            //size = (uint8_t)list.size();
            auto & pattern = *it;

            team = pattern.pattern->getTeam();
            if (pattern.pattern->line[pattern.posOnPattern] != team)
            {
                //removed extremity of line
                pattern.pattern->line[pattern.posOnPattern] = NOPLAYER;
            }
            else
            {
	      //std::cout << "pattern: start=" << std::to_string(pattern.pattern->posOfFirst) << " len=" << std::to_string(pattern.pattern->lineLength) << " dir=" << std::to_string(pattern.pattern->direction) << std::endl;

                removeFromMap(pattern.pattern, &it, &it_set);
                if (pattern.pattern->lineLength == 1)
                {
                    removeFromList(pattern.pattern);
                }
                else
                {
                    //full size of the second half, including extremity, excluding the position of the removed stone
                    uint8_t halfSize = pattern.pattern->lineLength - pattern.posOnPattern - (uint8_t)1;
                    if (halfSize >= 2)
                    {
                        //second half of pattern: create new pattern
                        if (halfSize == 2)
                        {
                            //1 stone left + extremity
                            if (onePatternAt(position + pattern.pattern->direction) == false)
                            {
                                //if the 1 stone is not part of any other pattern, create new 1-stone pattern
			      //std::cout << "2nd half: 1 stone" << std::endl;
                                patterns.push_front(Pattern(team, position + pattern.pattern->direction));
                                addToMap(&patterns.front());
                            }
                            addOSLastExtremity(pattern.pattern);
                        }
                        else
                        {
                            //new multiple-stone pattern (starting at position, since pattern dir is always positive)
			  //        std::cout << "2nd half: multiple stones" << std::endl;
                            patterns.push_front(Pattern(team, halfSize + (uint8_t) 1, NOPLAYER,
                                                        pattern.pattern->line[pattern.pattern->lineLength -
                                                                              (uint8_t) 1],
                                                        position, pattern.pattern->direction));
                            addToMap(&patterns.front());
                        }
                    }
                    else if (halfSize == 1)
                    {
                        //only the extremity
		      //std::cout << "2nd half: add OS" << std::endl;
                        addOSLastExtremity(pattern.pattern); //TODO: make 1-stone pattern only if no other pattern on this cell
                    }
                    //else: no second half to create

                    //first half of pattern
                    halfSize = pattern.posOnPattern;
                    if (halfSize >= 2)
                    {
                        if (halfSize == 2)
                        {
                            //1 stone: whatever happens, extremity is lost
                            addOSFirstExtremity(pattern.pattern);
                            PLIST<PatternRef> & singleStoneList = map[position - pattern.pattern->direction];
                            if (singleStoneList.begin() != singleStoneList.end())
                            {
                                //only one stone, and it is part of another pattern
			      //std::cout << "1st half: erased" << std::endl;
                                removeFromList(pattern.pattern);
                            }
                            else
                            {
                                //change pattern
			        //            std::cout << "1st half: change pattern" << std::endl;
                                pattern.pattern->breatAt(pattern.posOnPattern);
                                addToMap(pattern.pattern);
                            }
                        }
                        else
                        {
                            //change pattern
			  //      std::cout << "1st half: change pattern" << std::endl;
                            pattern.pattern->breatAt(pattern.posOnPattern);
                            addToMap(pattern.pattern);
                        }
                    }
                    else
                    {
                        //destroy pattern
		      //    std::cout << "1st half: erased, add OS" << std::endl;
                        addOSFirstExtremity(pattern.pattern); //TODO: make 1-stone pattern only if no other pattern on this cell
                        removeFromList(pattern.pattern);
                    }
                }
            }

            if (!it_set)
                ++it;
            //incFlexibleIterator(list, size, prev_it, it);
        }
    }
    //std::cout << *this << std::endl;
}

Team PatternManager::teamAt(boardPos_t pos) const
{
    return ((Team)board[pos]);
}

void PatternManager::removePattern(Pattern * pattern)
{
    addOSExtremities(pattern);

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

void PatternManager::removeFromMap(Pattern *pattern, PLIST<PatternRef>::iterator * used_it, bool * it_set)
{
    boardPos_t max = pattern->posOfFirst + pattern->lineLength * pattern->direction;
    for (boardPos_t pos = pattern->posOfFirst; pos < max; pos += pattern->direction)
    {
        for (PLIST<PatternRef>::iterator it = map[pos].begin(); it != map[pos].end(); ++it)
        {
            if ((*it).pattern == pattern)
            {
                if (used_it != NULL && it == *used_it)
                {
                    *used_it = map[pos].erase(it);
                    *it_set = true;
                }
                else
                {
                    map[pos].erase(it);
                }
                break;
            }
        }
        if (map[pos].empty())
            map.erase(pos);
    }
}

void PatternManager::removeFromMap(Pattern *pattern)
{
    boardPos_t max = pattern->posOfFirst + pattern->lineLength * pattern->direction;
    for (boardPos_t pos = pattern->posOfFirst; pos < max; pos += pattern->direction)
    {
        for (PLIST<PatternRef>::iterator it = map[pos].begin(); it != map[pos].end(); ++it)
        {
            if ((*it).pattern == pattern)
            {
                map[pos].erase(it);
                break;
            }
        }
        if (map[pos].empty())
            map.erase(pos);
    }
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
    map[position].push_front(PatternRef(pattern, posOnPattern));
}

void PatternManager::addOSExtremities(Pattern *pattern)
{
    //pattern is being removed: if its extremities are one stone, these become new one-stone patterns
    addOSFirstExtremity(pattern);
    addOSLastExtremity(pattern);
}

void PatternManager::addOSFirstExtremity(Pattern *pattern)
{
  //std::cout << "extr:first" << std::endl;
    if (pattern->line[0] > NOPLAYER &&
        onePatternAt(pattern->posOfFirst) == false)
    {
        addOneStone(pattern->line[0], pattern->posOfFirst);
    }
}

void PatternManager::addOSLastExtremity(Pattern *pattern)
{
  //std::cout << "extr:last" << std::endl;
    if (pattern->line[pattern->lineLength - 1] > NOPLAYER &&
        onePatternAt(pattern->posOfFirst + pattern->direction * (pattern->lineLength - (boardPos_t)1)) == false)
    {
        addOneStone(pattern->line[pattern->lineLength - 1], pattern->posOfFirst + (pattern->lineLength - (boardPos_t)1) * pattern->direction);
    }
}

int PatternManager::nbPatternsAt(boardPos_t pos)
{
    auto patterns = patternsAt(pos);
    return (patterns ? patterns->size() : 0);
}

bool PatternManager::onePatternAt(boardPos_t pos) const
{
    auto patterns = patternsAt(pos);
    return (patterns ? (patterns->begin() != patterns->end()) : false);
}

void PatternManager::addOneStone(Team team, boardPos_t position)
{
  //std::cout << "add one stone" << std::endl;
    patterns.push_front(Pattern(team, position));
    addToMap(&patterns.front(), position, 0);
}

void PatternManager::removeOSExtremities(Pattern *pattern)
{
    //if extremities of pattern are also on a 1-stone pattern, remove that 1-stone pattern
    if (pattern->line[0] != pattern->getTeam() && pattern->line[0] != NOPLAYER)
    {
        removeOneStone(pattern->posOfFirst);
    }
    if (pattern->line[pattern->lineLength - 1] != pattern->getTeam() && pattern->line[pattern->lineLength - 1] != NOPLAYER)
    {
        removeOneStone(pattern->posOfFirst + (pattern->lineLength - (boardPos_t)1) * pattern->direction);
    }
}

void PatternManager::removeOneStone(boardPos_t position)
{
    for (auto it = map[position].begin(); it != map[position].end(); ++it)
    {
        auto pat = &(*it);
        if (pat->pattern->lineLength == 1)
        {
            removeFromList(pat->pattern);
            map[position].erase(it);
            break;
        }
    }
}







reservList<PatternManager::line_s> PatternManager::boardRl = reservList<PatternManager::line_s>(128);

const boardPos_t PatternManager::checkMap[] = {
        0,
        -1,
        -XPBOARD - 1,
        -XPBOARD - 0,
        -XPBOARD + 1,
        +1,
        +XPBOARD + 1,
        +XPBOARD - 0,
        +XPBOARD - 1,
        -1, //back to start of list => no need for %
        -XPBOARD - 1,
        -XPBOARD - 0,
        -XPBOARD + 1
};

std::ostream &operator<<(std::ostream & out, const Core::PatternManager & pm)
{
    out << "-- PATTERNS" << std::endl;
    //for (auto& pattern : pm.getPatterns())
    for (auto it = pm.getPatterns().begin(); it != pm.getPatterns().end(); ++it)
    {
        auto& pattern = *it;
        out << (void*)&pattern;
        out << "\tlength=" << std::to_string((int)pattern.lineLength);
        out << "\tstartPos=" << pattern.posOfFirst;
        out << "\tdir=" << std::to_string((int)pattern.direction);
        out << "\tline=";
        for (int i = 0; i < pattern.lineLength; ++i)
            out << std::to_string((int)pattern.line[i]);
        out << std::endl;
    }
    out << "-- MAP" << std::endl;
    for (auto& entry : pm.getMap())
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
