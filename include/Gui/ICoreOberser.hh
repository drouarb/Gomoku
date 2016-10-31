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

        virtual void playGame(GamePlayers playerConfiguration) = 0;
        virtual void setRule(const std::string & rule, bool on) = 0;
    };
}

#endif