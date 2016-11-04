//
// Created by lewis_e on 31/10/16.
//

#include "CoreOberser.hh"
#include "Core.hh"

using namespace GUI;

CoreObserver::CoreObserver(Core::Core & core) : core(core)
{
    stop = true;
}

CoreObserver::~CoreObserver()
{ }

void CoreObserver::playGame(GamePlayers playerConfiguration)
{
    stop = true;
    core.playGame(playerConfiguration);
}

void CoreObserver::setRule(const std::string &rule, bool on)
{
    core.setRule(rule, on);
}

void CoreObserver::endGame()
{
    stop = false;
}

bool CoreObserver::gameIsRunning()
{
    return stop;
}
