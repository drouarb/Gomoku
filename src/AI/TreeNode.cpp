//
// Created by drouar_b on 11/25/16.
//

#include <math.h>
#include <algorithm>
#include <Core/BoardSeeker.hh>
#include "AI/TreeNode.hh"

AI::TreeNode::TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent) : plays(0), wins(0),
                                                                                 referee(gameState),
                                                                                 parent(parent), move(-1),
                                                                                 aiTeam(team) {
    this->moves = Core::BoardSeeker::getPlayPos(referee);
    childs.reserve(moves->size());
}

AI::TreeNode::TreeNode(Core::IReferee *gameState, Team team, AI::TreeNode *parent,
                       std::list<std::pair<boardPos_t, weight_t>> *moves) : plays(0), wins(0), referee(gameState),
                                                                            parent(parent), aiTeam(team) {
    boardPos_t move;
    bool play = false;

    do {
        move = moves->front().first;
        moves->pop_front();
    } while (!(play = referee->tryPlay(move)) && moves->size());
    if (!play) {
        delete(referee);
        throw std::domain_error("No more moves");
    }

    this->move = move;
    referee->tryPlay(move);
    this->moves = Core::BoardSeeker::getPlayPos(referee);
    childs.reserve(moves->size());
}


AI::TreeNode::~TreeNode() {
    for (auto c : childs) {
        delete (c);
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
    for (auto c : childs) {
        wins = c->getWins();
        plays = c->getPlays();

        if (c->aiTeam != referee->getPlayer())
            wins = plays - wins;

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

    for (auto c : childs) {
        wins = c->getWins();
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

void AI::TreeNode::backPropagate(int result) {
    plays += 1;
    if (result)
        wins += 1;
    if (parent)
        parent->backPropagate(result);
}

double AI::TreeNode::getPlays() const {
    return plays;
}

double AI::TreeNode::getWins() const {
    return wins;
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

