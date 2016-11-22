//
// Created by greg on 13/11/2016.
//

#include "BoardEvaluator.hh"

using namespace Core;



/*
const Core::BoardEvaluator::fct_t *Core::BoardEvaluator::fct = {
    t,
};
*/

int Core::BoardEvaluator::getValue(const Core::PatternManager *patternManager) {
    const PLIST<Pattern> &list = patternManager->getPatterns();
    int boardValue = 0;
    static int (*fct[])(Core::Pattern *) = {
            [](Pattern *p) { //0
                return 1;
            },
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
            defaultValue,
    };

    for (auto e : patternManager->getPatterns()) {
        if (e.lineLength > 20) {
            boardValue += defaultValue(&e);
            continue;
        }
        boardValue += fct[e.lineLength](&e);
    }
    return boardValue;
}

int BoardEvaluator::defaultValue(Pattern *p) {
    return 0;
}
