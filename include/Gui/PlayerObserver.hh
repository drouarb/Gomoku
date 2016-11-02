#ifndef PLAYEROBSERVER_HH_
#define PLAYEROBSERVER_HH_

#include "IPlayerObserver.hh"

namespace GUI
{
    class PlayerObserver : public IPlayerObserver
    {
    public:
        PlayerObserver();
        ~PlayerObserver();

        void setPlayer(Players::IHumain * player);
        Players::IPlayer * getPlayer() const;
        void sendPlay(uint8_t x, uint8_t y);

    private:
        Players::IPlayer * player;
    };
}

#endif