//
// Created by drouar_b on 11/25/16.
//

#include <Core/BoardSeeker.hh>
#include "AI/MonteCarlo.hh"

AI::MonteCarlo::MonteCarlo(Core::IReferee *referee, Team team) : team(team), root(new TreeNode(referee->clone(), team)),
                                                                 referee(referee) {

}

AI::MonteCarlo::~MonteCarlo() {

}

void AI::MonteCarlo::run() {
    TreeNode *next;
    std::map<int, double> moveList;

    sw.set();
    while (sw.elapsedMs() < 1000) {
        //TODO thread
        if ((next = root->getSimulationNode()) == NULL)
            break;
        simulate(next);
    }
    referee->tryPlay(root->getBestAction());
}

void AI::MonteCarlo::simulate(AI::TreeNode *node) {
    int nextMove;
    Core::IReferee *sim = node->getReferee()->clone();

    while (sim->getWinner() == NOPLAYER) {
        nextMove = Core::BoardSeeker::getBestPlay(sim);
        sim->tryPlay(nextMove);
    }
    node->backPropagate(sim->getWinner() == team);
    delete(sim);
}

