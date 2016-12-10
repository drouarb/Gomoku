//
// Created by greg on 13/11/2016.
//

#ifndef GOMOKU_BOARDEVALUATOR_HH
#define GOMOKU_BOARDEVALUATOR_HH

#include <cstring>
#include "Referee.hpp"
#include "PatternManager.hh"

namespace Core {



    class BoardEvaluator {

    private:

        struct value_t {
            int extremity_me[3];
            int extremity_enemy[3];

            int coef_me;
            int coef_enemy;

            value_t() {
                memset(this, 0, sizeof(*this));
            }
        };

        struct conf_t {
            value_t values[22];

            int pierres_mangees[9];

            conf_t() {
                memset(this, 0, sizeof(*this));
            }
        };

        conf_t *conf;

    public:
        BoardEvaluator();

        void parseFrom(const std::string &path);
        int32_t getValue(IReferee * referee, Team t) const;
        std::vector<std::pair<boardPos_t, weight_t>> * getInterestingMoves(IReferee *) const;
        std::vector<boardPos_t> * getAvailableMoves(IReferee *) const;

        static BoardEvaluator *getInstance();

    private:
        bool notMiddleOfNowhere(const PatternManager &, boardPos_t) const;
    };
}


#endif //GOMOKU_BOARDEVALUATOR_HH
