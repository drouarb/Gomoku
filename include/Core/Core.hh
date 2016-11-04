//
// Created by lewis_e on 28/10/16.
//

#ifndef GOMOKU_CORE_HH
#define GOMOKU_CORE_HH

#include "Definitions.hh"
#include "IGUI.hh"
#include "IPlayer.hh"
#include "IReferee.hh"
#include "IPlayer.hh"
#include "Rule.hh"
#include <string>
#include <map>
#include <list>

namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

        void playGame(enum GamePlayers player_config);
        void setRule(const std::string & rule, bool on);
        GUI::IGUI * gui;

    private:
         std::map<RuleID, Rule> rules;
        std::list<std::list<RuleID> > uniqueRules;
        IReferee * referee;
        Players::IPlayer * players[2]; //human first

        void destroyPlayer(int index);
        void createPlayerHuman(int index);
        void createPlayerAI(int index);
        void letPlayerPlay(int index);
        void feedRules();
    };
}

#endif //GOMOKU_CORE_HH
