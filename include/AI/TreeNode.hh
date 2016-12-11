//
// Created by drouar_b on 11/25/16.
//

#ifndef GOMOKU_TREENODE_HH
#define GOMOKU_TREENODE_HH

#include <vector>
#include <Core/Referee.hpp>
#include <mutex>

namespace AI {
    class TreeNode {
    public:
        TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent = NULL);
        TreeNode(Core::IReferee *gameState, Team team, TreeNode *parent, std::vector<std::pair<boardPos_t, weight_t>> *moves);
        ~TreeNode();

        TreeNode *getSimulationNode();
        TreeNode *getBestChild();
        int getBestAction() const;
        bool hasWinningChild() const;

        void backPropagate(int result, Team winner);

        int getMove() const;
        double getPlays() const;
        double getBlackWins() const;
        double getWhiteWins() const;
        void setParent(TreeNode *parent);
        TreeNode *getParent() const;
        Core::IReferee *getReferee() const;
        std::vector<TreeNode *> &getChilds();

    private:
        Team aiTeam;
        Core::IReferee *referee;

        unsigned int plays;
        unsigned int blackWins;
        unsigned int whiteWins;

        TreeNode *parent;
        std::vector<TreeNode *> childs;

        int move;
        std::vector<std::pair<boardPos_t, weight_t>> *moves;

        std::mutex mutex;
    };
}

#endif //GOMOKU_TREENODE_HH
