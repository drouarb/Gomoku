#ifndef COREOBSERVER_HH_
#define COREOBSERVER_HH_

#include "ICoreOberser.hh"

namespace Core
{
    class Core;
}

namespace GUI
{
    class CoreObserver : public ICoreObserver
    {
    public:
        CoreObserver(Core::Core &);
        ~CoreObserver();

        void playGame(GamePlayers playerConfiguration);
        void setRule(const std::string & rule, bool on);

    private:
        Core::Core & core;
    };
}

#endif