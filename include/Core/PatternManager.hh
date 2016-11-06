#ifndef PATTERN_MANAGER_HH_
#define PATTERN_MANAGER_HH_

#include "Pattern.hh"
#include <list>
#include <map>
#include <iostream>

#define PLIST std::list
#define PMAP std::map
#define OPPDIR(x) ((x) + 4)
#define ACTDIR(x) ((x) <= 4 ? OPPDIR(x) : x)

namespace Core
{
    struct PatternRef
    {
        Pattern * pattern;
        uint8_t posOnPattern;
    };

    class PatternManager
    {
    public:
        PatternManager();
        PatternManager(PatternManager &); //copy constructor
        ~PatternManager();

        PLIST<PatternRef> & operator[](boardPos_t);

        PLIST<Pattern> & getPatterns();
        const PLIST<Pattern> & getPatterns() const;
        PMAP<boardPos_t, PLIST<PatternRef> > getMap() const;
        void addStone(boardPos_t position, Team team);
        void removeStone(boardPos_t position);

    private:
        PLIST<Pattern> patterns;
        PMAP<boardPos_t, PLIST<PatternRef> > map;

        void doOppPattern(boardPos_t position, int i, Team team, PatternRef &pattern, boardPos_t &newlen, bool *done);
        void removePattern(Pattern * pattern);
        void removeFromList(Pattern * pattern);
        void removeFromMap(Pattern * pattern);
        Team teamAt(boardPos_t);
        void addToMap(Pattern * pattern);
        void addToMap(Pattern * pattern, boardPos_t position, uint8_t posOnPattern);
        void addOSExtremities(Pattern * pattern);
        void addOSFirstExtremity(Pattern * pattern);
        void addOSLastExtremity(Pattern * pattern);
        void addOneStone(Team team, boardPos_t position);
        void removeOSExtremities(Pattern *pattern);
        void removeOneStone(boardPos_t position);
        void incFlexibleIterator(PLIST<PatternRef> & list, int prev_size, PLIST<PatternRef>::iterator & prev_it, PLIST<PatternRef>::iterator & it);

        static const boardPos_t checkMap[];
        static const boardPos_t twoDistCircle[];
        static const boardPos_t dirRelations[];
    };
}

std::ostream& operator<< (std::ostream &, const Core::PatternManager &);

#endif
