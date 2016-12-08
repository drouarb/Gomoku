//
// Created by drouar_b on 11/25/16.
//

#include <math.h>
#include <algorithm>
#include <Core/BoardSeeker.hh>
#include <Core/BoardEvaluator.hh>
#include "AI/TreeNode.hh"

AI::TreeNode::TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent) : plays(0), whiteWins(0), blackWins(0),
                                                                                 referee(gameState),
                                                                                 parent(parent), move(-1),
                                                                                 aiTeam(team) {
    this->moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(referee);
    childs.reserve(moves->size());
}

AI::TreeNode::TreeNode(Core::IReferee *gameState, Team team, AI::TreeNode *parent,
                       std::vector<std::pair<boardPos_t, weight_t>> *moves) : plays(0), whiteWins(0), blackWins(0),
                                                                            referee(gameState),
                                                                            parent(parent), aiTeam(team) {
    this->move = moves->back().first;
    moves->pop_back();
    referee->tryPlay(move);
    this->moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(referee);
    childs.reserve(moves->size());
}


AI::TreeNode::~TreeNode() {
    for (auto &c : childs) {
        if (c) {
            c->parent = NULL;
            delete (c);
        }
    }
    delete (moves);
    delete (referee);
}

AI::TreeNode *AI::TreeNode::getSimulationNode() {
    if (moves->size()) {
        try {
            childs.push_back(new TreeNode(referee->clone(), aiTeam, this, moves));
            return childs.back();
        } catch (std::exception) {
            if (childs.size())
                return this->getBestChild()->getSimulationNode();
        }
    } else if (childs.size())
        return this->getBestChild()->getSimulationNode();
    return NULL;
}

AI::TreeNode *AI::TreeNode::getBestChild() {
    double wins;
    double plays;
    std::vector<double> values;

    values.reserve(childs.size());
    for (auto &c : childs) {
        wins = (referee->getPlayer() == WHITE ? c->getWhiteWins() : c->getBlackWins());
        plays = c->getPlays();

        values.push_back((wins / plays) + MC_EXPLORATION * sqrt(log(parent ? parent->getPlays() : 0) / plays));
    }
    return childs[(std::max_element(values.begin(), values.end()) - values.begin())];
}

int AI::TreeNode::getBestAction() const {
    int wins;
    int plays;
    int most_wins = -1;
    int most_plays = -1;
    std::vector<TreeNode *> bestActions;

    for (auto &c : childs) {
        wins = (aiTeam == WHITE ? c->getWhiteWins() : c->getBlackWins());
        plays = c->getPlays();

        if (plays > most_plays) {
            most_wins = wins;
            most_plays = plays;
            bestActions.clear();
            bestActions.push_back(c);
        } else if (plays == most_plays) {
            if (wins > most_wins) {
                most_wins = wins;
                bestActions.clear();
            }
            bestActions.push_back(c);
        }
    }
    if (bestActions.size() == 0)
        return -1;
    //TODO Random choose ???
    return bestActions.front()->getMove();
}

void AI::TreeNode::backPropagate(int result, Team winner) {
    plays += 1;
    if (winner == WHITE)
        whiteWins += result;
    if (winner == BLACK)
        blackWins += result;
    if (parent)
        parent->backPropagate(result, winner);
}

double AI::TreeNode::getPlays() const {
    return plays;
}

double AI::TreeNode::getBlackWins() const {
    return blackWins;
}

double AI::TreeNode::getWhiteWins() const {
    return whiteWins;
}

AI::TreeNode *AI::TreeNode::getParent() const {
    return parent;
}

Core::IReferee *AI::TreeNode::getReferee() const {
    return referee;
}

int AI::TreeNode::getMove() const {
    return move;
}

std::vector<AI::TreeNode *> &AI::TreeNode::getChilds() {
    return childs;
}

void AI::TreeNode::setParent(AI::TreeNode *parent) {
    TreeNode::parent = parent;
}

