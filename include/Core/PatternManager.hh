#ifndef PATTERN_MANAGER_HH_
#define PATTERN_MANAGER_HH_

#include "Pattern.hh"
#include <list>
#include <map>
#include <iostream>

#define PLIST std::list
#define PMAP std::map

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
        PatternManager(const PatternManager &); //copy constructor
        ~PatternManager();

        const PLIST<PatternRef> & operator[](boardPos_t) const;

        const PLIST<Pattern> & getPatterns() const;
        const PMAP<boardPos_t, PLIST<PatternRef> > getMap() const;
        void addStone(uint16_t position, Team team);
        void removeStone(uint16_t position);

    private:
        PLIST<Pattern> patterns;
        PMAP<boardPos_t, PLIST<PatternRef> > map;

        void addPattern();
        void removePattern();

        static const boardPos_t checkMap[];
    };
}

std::ostream& operator<< (std::ostream &, const Core::PatternManager &);

#endif
