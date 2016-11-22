//
// Created by greg on 13/11/2016.
//

#ifndef GOMOKU_BOARDEVALUATOR_HH
#define GOMOKU_BOARDEVALUATOR_HH

#include "PatternManager.hh"

namespace Core {

    class BoardEvaluator {

    private:
        typedef int (*fct_t)(Core::Pattern *);

/*
        static fct_t fct = NULL;
        */
        static int defaultValue(Pattern *p);
    public:
        static inline int getValue(const PatternManager *patternManager);
    };


}


#endif //GOMOKU_BOARDEVALUATOR_HH
