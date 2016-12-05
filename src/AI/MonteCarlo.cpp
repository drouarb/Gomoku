//
// Created by drouar_b on 11/25/16.
//

#include <Core/BoardSeeker.hh>
#include <Core/BoardEvaluator.hh>
#include "AI/MonteCarlo.hh"

AI::MonteCarlo::MonteCarlo(Core::IReferee *referee, Team team) : team(team), root(new TreeNode(referee->clone(), team)),
                                                                 referee(referee) {

}

AI::MonteCarlo::~MonteCarlo() {
    delete (root);
}

void AI::MonteCarlo::run() {
    int c = 0;
    int action;
    TreeNode *next;
    Stopwatch sw;

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
    Stopwatch sw;
    Core::IReferee *sim = node->getReferee()->clone();
    std::vector<std::pair<boardPos_t, weight_t>> *moves;

    while (sim->getWinner() == NOPLAYER && count < 361) {
        sw.set();
        moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(sim);
        std::cout << "Time " << sw.elapsedMs() << "nb " << moves->size() << std::endl;
        if (moves->size() == 0) {
            node->backPropagate(0, NOPLAYER);
            return;
        }
        sim->tryPlay(moves->back().first);
        delete(moves);
        count++;
    }
    node->backPropagate(1, sim->getWinner());
    delete(sim);
}

