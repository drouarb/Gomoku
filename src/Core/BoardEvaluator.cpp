//
// Created by greg on 13/11/2016.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "BoardEvaluator.hh"

using namespace Core;
using namespace boost::property_tree;

static BoardEvaluator *instance = NULL;

#define ADD_BY_TEAM(team, point, pattern) (pattern.getTeam() == team ? point : -point)

BoardEvaluator *BoardEvaluator::getInstance() {
    if (!instance) {
        instance = new BoardEvaluator();
    }
    return instance;
}

int32_t BoardEvaluator::getValue(const PatternManager *patternManager, IReferee *referee) const {
    ;
    return 0;
}

int32_t BoardEvaluator::getValue(const PatternManager *patternManager, IReferee *referee, Team t) const {
    int32_t totalValue = referee->getTeamEat(t) * this->conf->points_par_pierre_mangee;
    for (auto pattern : patternManager->getPatterns()) {
        if (pattern.lineLength > this->conf->max_values) {
            int exceed_rock = pattern.lineLength - this->conf->max_values;
            totalValue += ADD_BY_TEAM(t, this->conf->exceeded_values.points_par_pierre_en_plus * exceed_rock, pattern);
            uint8_t freeExtremity = 0;
            freeExtremity += ADD_BY_TEAM(t, (pattern.line[0] == 0 ? 1 : 0), pattern);
            freeExtremity += ADD_BY_TEAM(t, (pattern.lineLength > 0 && pattern.line[pattern.lineLength - 1] == 0 ? 1 : 0), pattern);
            totalValue += ADD_BY_TEAM(t, this->conf->exceeded_values.points_en_plus_en_fonction_des_extremites[freeExtremity], pattern);
            continue;
        }
        value_t &value = this->conf->values[pattern.lineLength];
        uint8_t freeExtremity = 0;
        freeExtremity += ADD_BY_TEAM(t, (pattern.line[0] == 0 ? 1 : 0), pattern);
        freeExtremity += ADD_BY_TEAM(t, (pattern.lineLength > 0 && pattern.line[pattern.lineLength - 1] == 0 ? 1 : 0), pattern);
        totalValue += ADD_BY_TEAM(t, value.extremity[freeExtremity], pattern);
    }
    return totalValue;
}


void BoardEvaluator::parseFrom(const std::string &path) {
    // Create a root
    ptree root;

    // Load the json file in this ptree
    read_json(path, root);

    // BOOST_FOREACH(boost::property_tree::ptree::value_type &v, root.get_child("values")) {
    //   std::cout << v.first << std::endl;
    // }

    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("values")) {

                    int len = child.second.get<int>("taille");

                    value_t *val = &conf->values[len];

                    this->conf->max_values = (this->conf->max_values < len ? len : this->conf->max_values);

                    val->size = len;
                    uint8_t c = 0;

                    BOOST_FOREACH(const ptree::value_type &child2,
                                  child.second.get_child("extremites")) {
                                    val->extremity[c] = child2.second.get_value<int>();
                                    c++;
                                }
                }
    uint8_t c = 0;
    conf->exceeded_values.points_par_pierre_en_plus = root.get_child(
            "exceeded_values.points_par_pierre_en_plus").get_value<int>();
    BOOST_FOREACH(ptree::value_type
                          child, root.get_child("exceeded_values.points_en_plus_en_fonction_des_extremites")) {
                    conf->exceeded_values.points_en_plus_en_fonction_des_extremites[c] = child.second.get_value<int>();
                    c++;
                }
    conf->points_par_pierre_mangee = root.get_child("points_par_pierre_mangée").get_value<int>();
}

