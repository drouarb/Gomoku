//
// Created by drouar_b on 12/2/16.
//

#include <Core/BoardEvaluator.hh>
#include <Helpers/Stopwatch.hh>
#include "AI/NodeCache.hh"

AI::NodeCache::NodeCache(Core::IReferee *referee) : work(ioService), running(false), rootRound(0),
                                                    root(new TreeNode(referee->clone(), WHITE)) {
    root->getReferee()->setPlayer(WHITE);
    for (int i = 0; i < THREADS_POOL; i++) {
        threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService));
    }
    rng = boost::random::taus88(time(NULL));
    rand = boost::random::uniform_int_distribution<>(0, XPBOARD * XPBOARD - 1);
    sim = 0;
}

AI::NodeCache::~NodeCache() {
    this->stop();
    delete (root);
}

void AI::NodeCache::threadTask(int threadId) {
    TreeNode *c;
    if ((c = root->getSimulationNode())) {
        simulate(c);
        sim++;
    }
    if (running)
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this, threadId));
    else
        threadLocks[threadId].unlock();
}

void AI::NodeCache::run() {
    if (running)
        return;
    running = true;
    for (int i = 0; i < THREADS_POOL; i++) {
        threadLocks[i].lock();
        ioService.post(boost::bind(&AI::NodeCache::threadTask, this, i));
    }
}

void AI::NodeCache::pause() {
    running = false;
    for (int i = 0; i < THREADS_POOL; i++) {
        threadLocks[i].lock();
        threadLocks[i].unlock();
    }
}

void AI::NodeCache::stop() {
    running = false;
    ioService.stop();
    threadpool.join_all();
}

int AI::NodeCache::getMove(Core::IReferee *referee, unsigned int ms) {
    int action;
    Stopwatch sw;
    TreeNode *oldRoot = NULL;

    sw.set();
    std::cout << "Check player" << std::endl;
    if (referee->getPlayer() != root->getReferee()->getPlayer()) {
        pause();
        std::cout << referee->getPlayer() << " | " << root->getReferee()->getPlayer() << " " << std::endl;
        std::cout << "Need step forward" << std::endl;
        std::cout << setNewRoot(referee, referee->getLastMove());
        std::cout << "Done" << std::endl;
        run();
    }

    //Take a break :)
    usleep((ms - sw.elapsedMs()) * 1000);
    pause();
    std::cout << "SIM" << sim << std::endl;

    action = root->getBestAction();
    if (action != -1) {
        referee->tryPlay(action);
        setNewRoot(referee, action);
    } else {
        std::cout << "Catastrophe, go Random" << std::endl;
        while (!referee->tryPlay(::rand() % (XBOARD * XBOARD)));
    }
    run();
    return action;
}

bool AI::NodeCache::setNewRoot(Core::IReferee *referee, int action) {
    bool found = false;
    TreeNode *oldRoot = root;

    for (auto &c : root->getChilds()) {
        if (c->getMove() == action) {
            c->setParent(NULL);
            root = c;
            c = NULL;
            found = true;
            break;
        }
    }
    if (root == oldRoot)
        root = new TreeNode(referee->clone(), referee->getPlayer());
    delete (oldRoot);
    return found;
}

void AI::NodeCache::simulate(AI::TreeNode *node) {
    Core::IReferee *sim = node->getReferee()->clone();

    int rc;
    int count = 0;
    std::vector<std::pair<boardPos_t, weight_t>> *moves;

    while (sim->getWinner() == NOPLAYER && count < 361) {
        /*moves = Core::BoardEvaluator::getInstance()->getInterestingMoves(sim);
        if (moves->size() == 0) {
            node->backPropagate(0, NOPLAYER);
            return;
        }
        sim->tryPlay(moves->back().first);
        delete (moves);*/
        rc = 0;
        while (sim->tryPlay(rand(rng)) == false && (++rc < XPBOARD * XPBOARD));
        if (rc == XPBOARD * XPBOARD)
            break;
        ++count;
    }
    node->backPropagate(1, sim->getWinner());
    delete (sim);

}

AI::NodeCache *AI::NodeCache::getInstance(Core::IReferee *referee) {
    static NodeCache *cache = NULL;
    static Core::IReferee *save = NULL;

    if (referee && referee != save) {
        std::cout << "New nodecache" << (void*)referee << std::endl;
        if (cache)
            delete (cache);
        cache = new NodeCache(referee);
        cache->run();
        save = referee;
    }
    return cache;
}
