//
// Created by drouar_b on 11/25/16.
//

#ifndef GOMOKU_TREENODE_HH
#define GOMOKU_TREENODE_HH

#include <vector>
#include <Core/Referee.hpp>

namespace AI {
    class TreeNode {
    public:
        TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent = NULL);
        TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent, int move);
        ~TreeNode();

        TreeNode *getSimulationNode();
        TreeNode *getBestChild();
        void backPropagate(int result);

        int getBestAction() const;
        double getPlays() const;
        double getWins() const;
        TreeNode *getParent() const;
        Core::IReferee *getReferee() const;
        int getMove() const;

    private:
        Team aiTeam;
        int plays;
        int wins;
        int move;
        TreeNode *parent;
        fastList<boardPos_t> *moves;
        std::vector<TreeNode *> childs;
        Core::IReferee *referee;
    };
}

#endif //GOMOKU_TREENODE_HH
