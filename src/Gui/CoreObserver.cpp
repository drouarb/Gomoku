//
// Created by lewis_e on 31/10/16.
//

#include "CoreOberser.hh"
#include "Core.hh"

using namespace GUI;

CoreObserver::CoreObserver(Core::Core & core) : core(core)
{ }

CoreObserver::~CoreObserver()
{ }

void CoreObserver::playGame(GamePlayers playerConfiguration)
{
    core.playGame(playerConfiguration);
}

void CoreObserver::setRule(const std::string &rule, bool on)
{
    core.setRule(rule, on);
}