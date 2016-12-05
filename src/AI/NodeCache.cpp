//
// Created by drouar_b on 12/2/16.
//

#include <Core/BoardEvaluator.hh>
#include <Helpers/Stopwatch.hh>
#include "AI/NodeCache.hh"

AI::NodeCache::NodeCache(Core::IReferee *referee) : work(ioService), running(false), rootRound(0),
                                                    root(new TreeNode(referee->clone(), WHITE)) {
    for (int i = 0; i < THREADS_POOL; i++) {
        threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService));
    }
}

AI::NodeCache::~NodeCache() {
    this->stop();
    delete (root);
}

void AI::NodeCache::threadTask() {
    TreeNode *c = root->getSimulationNode();
    simulate(c);
    if (running)
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this));
}

void AI::NodeCache::run() {
    running = true;
    for (int i = 0; i < THREADS_POOL; i++) {
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this));
    }
}

void AI::NodeCache::stop() {
    ioService.stop();
    threadpool.join_all();
}

int AI::NodeCache::getMove(Core::IReferee *referee, unsigned int ms) {
    int action;
    Stopwatch sw;
    TreeNode *oldRoot = NULL;

    sw.set();
    if (referee->getNbrPlay() != rootRound) {
        for (auto &c : root->getChilds()) {
            if (c->getMove() == referee->getLastMove()) {
                oldRoot = root;
                c->setParent(NULL);
                root = c;
                c = NULL;
                delete(oldRoot);
                ++rootRound;
                std::cout << "Found parent in tree" << std::endl;
                break;
            }
        }
    }
    if (oldRoot == NULL) {
        oldRoot = root;
        root = new TreeNode(referee->clone(), referee->getPlayer());
        std::cout << "No Parent regenerate" << std::endl;
        delete(oldRoot);
    }
    //Take a break :)
    usleep((ms * 1000) - sw.elapsedUs());
    action = root->getBestAction();
    if (action)
        referee->tryPlay(action);
    return action;
}

void AI::NodeCache::simulate(AI::TreeNode *node) {
    int count = 0;
    Core::IReferee *sim = node->getReferee()->clone();
    std::vector<std::pair<boardPos_t, weight_t>> *moves;

    while (sim->getWinner() == NOPLAYER && count < 361) {
        moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(sim);
        if (moves->size() == 0) {
            node->backPropagate(0, NOPLAYER);
            return;
        }
        sim->tryPlay(moves->back().first);
        delete(moves);
        ++count;
    }
    node->backPropagate(1, sim->getWinner());
    delete(sim);

}
