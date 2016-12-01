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
    int c = 0;
    int action;
    TreeNode *next;

    sw.set();
    while (sw.elapsedMs() < 1000) {
        //TODO thread
        if ((next = root->getSimulationNode()) == NULL)
            break;
        std::cout << "SIMULATION=============================================" << std::endl;
        simulate(next);
        std::cout << "END_SIMULATION=============================================" << std::endl;
        c++;
    }
    action = root->getBestAction();
    std::cout << "Simulations: " << c << ", Action: " << action << std::endl;
    if (action > 0)
        referee->tryPlay(action);
}

void AI::MonteCarlo::simulate(AI::TreeNode *node) {
    int count = 0;
    bool play;
    Core::IReferee *sim = node->getReferee()->clone();
    std::list<std::pair<boardPos_t, weight_t>> *moves;

    while (sim->getWinner() == NOPLAYER && count < 300) {
        play = false;
        moves = Core::BoardSeeker::getPlayPos(sim);
        while (moves->size() > 0 && !(play = sim->tryPlay(moves->front().first)))
            moves->pop_front();
        delete(moves);
        if (!play) {
            node->backPropagate(0);
            return;
        }
        count++;
    }
    node->backPropagate(sim->getWinner() == team);
    delete(sim);
}

