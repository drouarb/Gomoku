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
#define MAX_VALUE 2000000000
#define WIN_VALUE(team, winner) (winner == team ? MAX_VALUE : -MAX_VALUE)


static bool cmpWeightVect(const std::pair<boardPos_t, weight_t>& pos1, const std::pair<boardPos_t, weight_t>& pos2)
{
    return (pos1.second < pos2.second);
}

BoardEvaluator *BoardEvaluator:: getInstance() {
    if (!instance) {
        instance = new BoardEvaluator();
    }
    return instance;
}

int32_t BoardEvaluator::getValue(IReferee * referee, Team t) const {

    if (referee->getWinner() > NOPLAYER)
    {
        return (WIN_VALUE(t, referee->getWinner()));
    }

    int32_t totalValue = 0;

    totalValue += conf->pierres_mangees[referee->getTeamEat(t)]
                - conf->pierres_mangees[referee->getTeamEat(OPPTEAM(t))];

    for (auto & pattern : referee->getBoOp()->getPatternManager().getPatterns()) {
        totalValue += ADD_BY_TEAM(t,
                                  conf->values[pattern.lineLength].extremity[(pattern.line[0] == NOPLAYER) + (pattern.line[pattern.lineLength - 1] == NOPLAYER)],
                                  pattern);
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

                    int len = child.second.get<int>("taille") + 2;

                    value_t *val = &conf->values[len];

                    uint8_t c = 0;

                    BOOST_FOREACH(const ptree::value_type &child2,
                                  child.second.get_child("extremites")) {
                                    val->extremity[c] = child2.second.get_value<int>();
                                    c++;
                                }
                }
    uint8_t c = 0;

    int extra_stone_points = root.get_child("points_par_pierre_en_plus").get_value<int>();
    for (int i = 8; i < 22; ++i)
    {
        for (int e = 0; e < 3; ++e)
        {
            conf->values[i].extremity[e] = conf->values[i - 1].extremity[e] + extra_stone_points;
        }
    }

    conf->pierres_mangees[2] = root.get_child("points_pour_2_pierres_mangées").get_value<int>();
    conf->pierres_mangees[4] = root.get_child("points_pour_4_pierres_mangées").get_value<int>();
    conf->pierres_mangees[6] = root.get_child("points_pour_6_pierres_mangées").get_value<int>();
    conf->pierres_mangees[8] = root.get_child("points_pour_8_pierres_mangées").get_value<int>();
}

BoardEvaluator::BoardEvaluator() {
    this->conf = new conf_t;
    this->parseFrom("AI_conf.json");
}

std::vector<std::pair<boardPos_t, weight_t>> *BoardEvaluator::getInterestingMoves(IReferee * referee) const
{
    auto * vect = new std::vector<std::pair<boardPos_t, weight_t>>();

    if (referee->getBoOp()->getPatternManager().getPatterns().empty())
    {
        vect->push_back(std::pair<boardPos_t, weight_t>(9 * XBOARD + 9, 1));
        return (vect);
    }
    vect->reserve(32);

    std::cout << "before " << std::to_string(referee->getPlayer()) << " " << std::to_string(referee->getTeamEat(referee->getPlayer())) << std::endl;
    boardPos_t playPos;
    for (boardPos_t y = 0; y < 19; ++y)
    {
        for (boardPos_t x = 0; x < 19; ++x)
        {
            if (notMiddleOfNowhere(referee, PatternManager::getPPos(x, y)) && referee->tryPlay(x, y))
            {
                vect->push_back(std::pair<boardPos_t, weight_t>(y * XBOARD + x, getValue(referee, referee->getPlayer())));
                referee->undoLastMove();
            }
        }
    }
    std::cout << "after " << std::to_string(referee->getPlayer()) << " " << std::to_string(referee->getTeamEat(referee->getPlayer())) << std::endl;

    std::sort(vect->begin(), vect->end(), cmpWeightVect);

    return (vect);
}

bool BoardEvaluator::notMiddleOfNowhere(IReferee * referee, boardPos_t pos) const
{
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[1]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[2]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[3]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[4]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[5]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[6]))
        return (true);
    if (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[7]))
        return (true);
    return (referee->getBoOp()->getPatternManager().onePatternAt(pos + PatternManager::checkMap[8]));
}
