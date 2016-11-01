#ifndef IGUI_HH_
#define IGUI_HH_

#include "IPlayer.hh"
#include "Definitions.hh"
#include "ICoreOberser.hh"
#include "IPlayerObserver.hh"
#include <string>
#include <list>
#include <map>

namespace GUI
{
    class IGUI
    {
    public:
        ~IGUI() { }
        
        virtual void init(ICoreObserver *) = 0;
        virtual void registerPlayer(Players::IPlayer *) = 0;
        virtual void unregisterPlayer(Players::IPlayer *) = 0;
        virtual void feedBoard(const GameBoard_t &) = 0;
        virtual void feedRules(std::list<std::pair<std::string, bool>> rules) = 0;
        virtual void setCurrentPlayer(Players::IPlayer *) = 0;
        virtual void startGame() = 0;
        virtual void endGame(const std::string & winner_name) = 0;
    };
}

#endif