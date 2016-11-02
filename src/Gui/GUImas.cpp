#include "GUImas.hh"
#include <iostream>

using namespace GUI;

GUImas::GUImas()
{ }

GUImas::~GUImas()
{ }

void GUImas::init(ICoreObserver *)
{
    std::cout << "init" << std::endl;
}

void GUImas::registerPlayer(Players::IPlayer * player)
{
    std::cout << "register player " << (void*)player << std::endl;
}

void GUImas::unregisterPlayer(Players::IPlayer * player)
{
    std::cout << "unregister player " << (void*)player << std::endl;
}

void GUImas::feedBoard(const GameBoard_t &)
{
    std::cout << "feed board" << std::endl;
}

void GUImas::feedRules(std::list<std::pair<std::string, bool>> rules)
{
    std::cout << "feed rules" << std::endl;
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;
}

void GUImas::setCurrentPlayer(const std::string &name)
{ }

void GUImas::startGame()
{ }

void GUImas::endGame(const std::string &winner_name)
{ }