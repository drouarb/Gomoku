#ifndef IPLAYEROBSERVER_HH_
#define IPLAYEROBSERVER_HH_

#include "Definitions.hpp"
#include "IHuman.hh"
#include <string>

namespace GUI
{
    class IPlayerObserver
    {
    public:
        ~IPlayerObserver() { }

        virtual void setPlayer(Players::IHumain * player) = 0;
        virtual Players::IPlayer * getPlayer() const = 0;
        virtual void sendPlay(uint8_t x, uint8_t y) = 0;
    };
}

#endif
