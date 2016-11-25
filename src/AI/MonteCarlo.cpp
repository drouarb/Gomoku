//
// Created by drouar_b on 11/25/16.
//

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
    //TODO betterTryPlay
    referee->tryPlay(root->getBestAction(), 0);
}

void AI::MonteCarlo::simulate(AI::TreeNode *node) {
    int nextMove;
    Core::IReferee *sim = node->getReferee()->clone();

    while (sim->getWinner() == NOPLAYER) {
        //TODO get next move
        sim->tryPlay(nextMove, nextMove);
    }
    node->backPropagate(sim->getWinner() == team);
    delete(sim);
}

