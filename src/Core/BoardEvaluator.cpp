//
// Created by greg on 13/11/2016.
//

#include "BoardEvaluator.hh"

const std::map<std::pair<uint8_t, uint8_t> ,uint8_t> Core::BoardEvaluator::values = {
        {{0, 0}, 0}
};

int Core::BoardEvaluator::getValue(const Core::PatternManager *patternManager) {
    const PLIST<Pattern> &list = patternManager->getPatterns();
    int boardValue = 0;
    for (auto i : list) {
        const std::pair<uint8_t, uint8_t> &pair1 = std::pair<uint8_t, uint8_t>(*i.line, i.lineLength);
        try {
            uint8_t value = values.at(pair1);
            boardValue += value;
        } catch (const std::out_of_range &ignored) {
        }
    }
    return boardValue;
}
