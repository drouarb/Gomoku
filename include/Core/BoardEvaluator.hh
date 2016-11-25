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
            int size;
            int extremity[3];

            value_t() {
                memset(this, 0, sizeof(*this));
            }
        };

        struct exceeded_values_t {
            int points_par_pierre_en_plus;
            int points_en_plus_en_fonction_des_extremites[3];
        };

        struct conf_t {
            value_t values[21];
            exceeded_values_t exceeded_values;
            int max_values;

            int points_par_pierre_mangee;

            conf_t() {
                memset(this, 0, sizeof(*this));
            }
        };


        conf_t *conf;

    public:
        void parseFrom(const std::string &path);
        inline int32_t getValue(const PatternManager *patternManager, IReferee *referee) const;
        inline int32_t getValue(const PatternManager *patternManager, IReferee *referee, Team t) const;

        static inline BoardEvaluator *getInstance();
    };


}


#endif //GOMOKU_BOARDEVALUATOR_HH
