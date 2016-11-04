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
        PatternManager(PatternManager &); //copy constructor
        ~PatternManager();

      PLIST<PatternRef> & operator[](boardPos_t);

      PLIST<Pattern> & getPatterns();
      PMAP<boardPos_t, PLIST<PatternRef> > getMap() const;
      void addStone(uint16_t position, Team team);
        void removeStone(uint16_t position);

    private:
        PLIST<Pattern> patterns;
        PMAP<boardPos_t, PLIST<PatternRef> > map;

        void addPattern();
        void removePattern();

        static const boardPos_t checkMap[];
        static const boardPos_t twoDistCircle[];
    };
}

std::ostream& operator<< (std::ostream &, Core::PatternManager &);

#endif
