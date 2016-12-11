//
// Created by drouar_b on 12/2/16.
//

#ifndef GOMOKU_NODECACHE_HH
#define GOMOKU_NODECACHE_HH

#include <boost/random/taus88.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "TreeNode.hh"

namespace AI {
    class NodeCache {
    public:
        NodeCache(Core::IReferee *referee);
        ~NodeCache();

        void run();
        void stop();
        void pause();

        void threadTask(int threadId);
        int getMove(Core::IReferee *referee, unsigned int ms = 0);

        int rand(int max);
        TreeNode *getRoot() const;
        static NodeCache *getInstance(Core::IReferee *referee);

    private:
        void simulate(TreeNode *node);
        bool setNewRoot(Core::IReferee *referee, int action);

    private:
        bool running;
        TreeNode *root;
        unsigned int rootRound;
        std::mutex threadLocks[THREADS_POOL];

        boost::random::taus88 rng;
        static const std::array<boost::random::uniform_int_distribution<>, 361> randers;

        boost::thread_group threadpool;
        boost::asio::io_service ioService;
        boost::asio::io_service::work work;
    };
}

#endif //GOMOKU_NODECACHE_HH
