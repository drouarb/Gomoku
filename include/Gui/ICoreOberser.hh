#ifndef ICOREOBSERVER_HH_
#define ICOREOBSERVER_HH_

#include "Definitions.hpp"
#include <string>

namespace GUI
{
    class ICoreObserver
    {
    public:
        ~ICoreObserver() { }

        virtual void playGame(GamePlayers playerConfiguration) = 0;
        virtual void endGame() = 0;
        virtual bool gameIsRunning() = 0;
        virtual void setRule(const std::string & rule, bool on) = 0;
    };
}

#endif
