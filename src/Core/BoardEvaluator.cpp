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


static bool cmpWeight(const std::pair<boardPos_t, weight_t>& pos1, const std::pair<boardPos_t, weight_t>& pos2)
{
    return (pos1.second > pos2.second);
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
        if (referee->getPlayer() == pattern.getTeam()) {
            totalValue += ADD_BY_TEAM(t, conf->values[pattern.lineLength].extremity_enemy[(pattern.line[0] == NOPLAYER) +
                                                                        (pattern.line[pattern.lineLength - 1] ==
                                                                         NOPLAYER)], pattern);
        } else {
            totalValue += ADD_BY_TEAM(t, conf->values[pattern.lineLength].extremity_me[(pattern.line[0] == NOPLAYER) + (pattern.line[pattern.lineLength - 1] == NOPLAYER)], pattern);
        }
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

                    val->coef_me = child.second.get<int>("coef_me");
                    val->coef_enemy = child.second.get<int>("coef_enemy");
                    BOOST_FOREACH(const ptree::value_type &child2,
                                  child.second.get_child("extremites")) {
                                    val->extremity_me[c] = child2.second.get_value<int>() * val->coef_me;
                                    val->extremity_enemy[c] = child2.second.get_value<int>() * val->coef_enemy;
                                    c++;
                                }
                }
    uint8_t c = 0;

    int extra_stone_points = root.get_child("points_par_pierre_en_plus").get_value<int>();
    for (int i = 8; i < 22; ++i)
    {
        for (int e = 0; e < 3; ++e)
        {
            conf->values[i].extremity_me[e] = conf->values[i - 1].extremity_me[e] + extra_stone_points;
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

static bool checkPatterns(IReferee * ref1, IReferee * ref2)
{
    for (int i = 0; i < PBOARDSIZE; ++i)
    {
        if (ref1->getBoOp()->getPatternManager().getMap()[i].size() != ref2->getBoOp()->getPatternManager().getMap()[i].size())
            return (false);
        for (auto patref : ref1->getBoOp()->getPatternManager().getMap()[i])
        {
            bool found_same = false;
            for (auto patref2 : ref2->getBoOp()->getPatternManager().getMap()[i])
            {
                if (patref.posOnPattern == patref2.posOnPattern && *patref.pattern == *patref2.pattern)
                    found_same = true;
            }
            if (found_same == false)
                return (false);
        }
    }
    return (true);
}

std::vector<std::pair<boardPos_t, weight_t>> *BoardEvaluator::getInterestingMoves(IReferee * referee) const
{
    auto * vect = new std::vector<std::pair<boardPos_t, weight_t>>();

    if (referee->getBoOp()->getPatternManager().getPatterns().empty())
    {
        int middle = XBOARD * 9 + 9;
        for (int i = 0; i < PBOARDSIZE; ++i)
            if (referee->getBoOp()->boardAt(i) == NOPLAYER && i != middle)
                vect->push_back(std::pair<boardPos_t, weight_t>(i, 0));
        vect->push_back(std::pair<boardPos_t, weight_t>(middle, 0));
        return (vect);
    }
    vect->reserve(64);

    Team player = OPPTEAM(referee->getPlayer());
    Team oppPlayer = OPPTEAM(player);
    //TODO: for some reason, I can't seem to sort the vector in the right order. So for now, weights of the opposite team are calculated.


    referee->setPlayer(OPPTEAM(referee->getPlayer()));
    weight_t initial_val = getValue(referee, player);
    referee->setPlayer(OPPTEAM(referee->getPlayer()));

    for (int i = 0; i < PBOARDSIZE; ++i)
    {
        if (referee->getBoOp()->getPatternManager().teamAt(i) == NOPLAYER &&
                notMiddleOfNowhere(referee->getBoOp()->getPatternManager(), i))
        {
            if (referee->tryPlay(i))
            {
                weight_t val = getValue(referee, player);
                referee->undoLastMove();

                //see the influence of preventing the opposite player from playing this move
                referee->setPlayer(OPPTEAM(referee->getPlayer()));
                if (referee->tryPlay(i))
                {
                    referee->setPlayer(OPPTEAM(referee->getPlayer()));
                    val += getValue(referee, oppPlayer) + initial_val;
                    referee->undoLastMove();
                }
                else
                    referee->setPlayer(OPPTEAM(referee->getPlayer()));

                vect->push_back(std::pair<boardPos_t, weight_t>(i, val));
            }
        }
    }

    std::sort(vect->begin(), vect->end(), &cmpWeight);

    return (vect);
}

std::vector<boardPos_t> *BoardEvaluator::getAvailableMoves(IReferee * referee) const
{
    auto * vect = new std::vector<boardPos_t>();

    vect->reserve(64);

    for (int i = 0; i < PBOARDSIZE; ++i)
    {
        if (referee->getBoOp()->getPatternManager().teamAt(i) == NOPLAYER &&
            notMiddleOfNowhere(referee->getBoOp()->getPatternManager(), i))
        {
            vect->push_back(i);
        }
    }

    return (vect);
}

bool BoardEvaluator::notMiddleOfNowhere(const PatternManager & pm, boardPos_t pos) const
{
    if (pm.onePatternAt(pos + PatternManager::checkMap[1]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[2]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[3]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[4]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[5]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[6]))
        return (true);
    if (pm.onePatternAt(pos + PatternManager::checkMap[7]))
        return (true);
    return (pm.onePatternAt(pos + PatternManager::checkMap[8]));
}
