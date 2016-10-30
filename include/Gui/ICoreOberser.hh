#ifndef ICOREOBSERVER_HH_
#define ICOREOBSERVER_HH_

#include "Definitions.hh"
#include <string>

namespace GUI
{
    class ICoreObserver
    {
    public:
        ~ICoreObserver() { }

        virtual void playGame(GamePlayers playerConfiguration);
        virtual void setRule(const std::string & rule, bool on);
    };
}

#endif