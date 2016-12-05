//
// Created by drouar_b on 12/2/16.
//

#ifndef GOMOKU_NODECACHE_HH
#define GOMOKU_NODECACHE_HH

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

        void threadTask();
        int getMove(Core::IReferee *referee, unsigned int ms = 0);

    private:
        void simulate(TreeNode *node);

    private:
        bool running;
        TreeNode *root;
        unsigned int rootRound;

        boost::thread_group threadpool;
        boost::asio::io_service ioService;
        boost::asio::io_service::work work;
    };
}

#endif //GOMOKU_NODECACHE_HH
