//
// Created by lewis_e on 28/10/16.
//

#ifndef GOMOKU_CORE_HH
#define GOMOKU_CORE_HH

#include "Definitions.hh"
//#include "IGUI.hh"
#include "IPlayer.hh"
#include "IReferee.hh"
#include "IPlayer.hh"
#include <string>
#include <list>
#include <map>
#include <mutex>

namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

        void playGame(enum GamePlayers player_config);
        void setRule(const std::string & rule, bool on);

    private:
        std::mutex mutex;
        //IGUI * gui;
        std::list<std::pair<std::string, bool> > rules;
        std::list<std::list<std::string> > uniqueRules;
        IReferee * referee;
        Players::IPlayer * players[2];

        void sendRules();
    };
}

#endif //GOMOKU_CORE_HH
