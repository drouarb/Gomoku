//
// Created by greg on 13/11/2016.
//

#ifndef GOMOKU_BOARDEVALUATOR_HH
#define GOMOKU_BOARDEVALUATOR_HH

#include "PatternManager.hh"

namespace Core {

    class BoardEvaluator {
    private:
        static const std::map<std::pair<uint8_t, uint8_t > , uint8_t > values;
    public:
        static inline int getValue(const PatternManager *patternManager);
    };


}


#endif //GOMOKU_BOARDEVALUATOR_HH
