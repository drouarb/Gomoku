//
// Created by drouar_b on 11/25/16.
//

#ifndef GOMOKU_MONTECARLO_HH
#define GOMOKU_MONTECARLO_HH

#include <vector>
#include <Core/Definitions.hh>
#include <Helpers/Stopwatch.hh>
#include "TreeNode.hh"

namespace AI {
    class MonteCarlo {
    public:
        MonteCarlo(Core::IReferee *referee, Team team);
        ~MonteCarlo();

        void run();
        void simulate(TreeNode *node);

    private:
        Team team;
        TreeNode *root;
        Stopwatch sw;
        Core::IReferee *referee;
    };
}

#endif //GOMOKU_MONTECARLO_HH
