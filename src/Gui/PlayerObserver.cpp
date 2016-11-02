#include "PlayerObserver.hh"

using namespace GUI;

PlayerObserver::PlayerObserver() : player(NULL)
{ }

PlayerObserver::~PlayerObserver()
{ }

void PlayerObserver::setPlayer(Players::IHumain *player)
{
    this->player = player;
}

Players::IPlayer * PlayerObserver::getPlayer() const
{
    return (this->player);
}

void PlayerObserver::sendPlay(uint8_t x, uint8_t y)
{
    if (player != NULL && dynamic_cast<Players::IHumain *>(player) != NULL)
    {
        dynamic_cast<Players::IHumain *>(player)->tryPlay(x, y);
    }
}