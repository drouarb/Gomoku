#ifndef PATTERN_MANAGER_HH_
#define PATTERN_MANAGER_HH_

#include "Pattern.hh"
#include "Helpers/fastList.hpp"
#include "Helpers/reservationList.hpp"
#include "Helpers/rotatingArray.hpp"
#include "Helpers/rotatingVector.hpp"
#include <map>
#include <iostream>

#define PLIST fastList<Pattern, 16>
//#define PLIST rotatingVector<Pattern>
//#define MAP_ENTRY PLIST<PatternRef>
#define MAP_ENTRY rotatingArray<PatternRef, 8>
#define OPPDIR(x) ((x) + 4)
#define ACTDIR(x) ((x) <= 4 ? OPPDIR(x) : x)

#define XPBOARD (XBOARD + 2)
#define PBOARDSIZE (XPBOARD * XPBOARD)

namespace Core
{
    struct PatternRef
    {
        PatternRef();
        PatternRef(Pattern *, uint8_t);
        ~PatternRef();

        Pattern * pattern;
        uint8_t posOnPattern;
    };

    class PatternManager
    {
    public:
        PatternManager();
        PatternManager(const PatternManager &);
        ~PatternManager();
        
        typedef MAP_ENTRY PMap[PBOARDSIZE];
        typedef Team PGameBoard_t[PBOARDSIZE];

        PatternManager & operator=(const PatternManager &);
        bool operator==(const PatternManager &);
        MAP_ENTRY & operator[](boardPos_t);

        static boardPos_t getPPos(boardPos_t x, boardPos_t y);

        PLIST & getPatterns();
        const PLIST & getPatterns() const;
        const PMap & getMap() const;
        const MAP_ENTRY & patternsAt(boardPos_t pos) const;
        void addStone(boardPos_t position, Team team);
        void removeStone(boardPos_t position);
        Team teamAt(boardPos_t position) const;
        bool onePatternAt(boardPos_t) const;

    private:
        PLIST patterns;
        PMap map;
        PGameBoard_t board;


        bool addMiddle(boardPos_t position, Team team);
        void doOppPattern(boardPos_t position, int i, Team team, PatternRef &pattern, boardPos_t &newlen, bool *done);
        bool isAligned(PatternRef &, int dir);
        void removePattern(Pattern * pattern);
        void removeFromList(Pattern * pattern);
        void removeFromMap(Pattern * pattern, MAP_ENTRY::iterator * it_being_used, bool * it_set);
        void removeFromMap(Pattern * pattern);
        void addToMap(Pattern * pattern);
        void addToMap(Pattern * pattern, boardPos_t position, uint8_t posOnPattern);
        void addOSExtremities(Pattern * pattern);
        void addOSFirstExtremity(Pattern * pattern);
        void addOSLastExtremity(Pattern * pattern);
        void addOneStone(Team team, boardPos_t position);
        void removeOSExtremities(Pattern *pattern);
        void removeOneStone(boardPos_t position);

    public:
        static const boardPos_t checkMap[];
    };
}

std::ostream& operator<< (std::ostream &, const Core::PatternManager &);

#endif
