#include "GUImas.hh"
#include "PlayerObserver.hh"
#include <iostream>

using namespace GUI;

GUImas::GUImas()
{
    players[0] = NULL;
    players[1] = NULL;
}

GUImas::~GUImas()
{ }

void GUImas::init(ICoreObserver * coreObserver)
{
    std::cout << "init" << std::endl;

    this->coreObserver = coreObserver;
    std::string input;
    std::cout << "> ";
    while (std::cin >> input)
    {
        if (input == "play")
        {
            coreObserver->playGame(TWOPLAYERS);
        }
        else
        {
            std::cout << "Just enter \'play\', goddamit." << std::endl;
        }
        std::cout << "> ";
    }
}

void GUImas::registerPlayer(Players::IPlayer * player)
{
    std::cout << "register player " << (void*)player << std::endl;
    PlayerObserver * po = new PlayerObserver();
    po->setPlayer(dynamic_cast<Players::IHumain *>(player));
    if (players[0] == NULL)
        players[0] = po;
    else
        players[1] = po;
}

void GUImas::unregisterPlayer(Players::IPlayer * player)
{
    std::cout << "unregister player " << (void*)player << std::endl;
    if (players[1]->getPlayer() == player)
        players[1] = NULL;
    else
        players[0] = NULL;
}

void GUImas::feedBoard(const GameBoard_t &)
{
    std::cout << "feed board" << std::endl;
}

void GUImas::feedRules(std::list<std::pair<std::string, bool>> rules)
{
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;
}

void GUImas::setCurrentPlayer(Players::IPlayer * player)
{
    current = player;
}

void GUImas::startGame()
{ }

void GUImas::endGame(const std::string &winner_name)
{ }

void GUImas::showErrror(std::string)
{
    std::cout << "nope" << std::endl;
}

void GUImas::prompt()
{
    std::cout << "prompt: " << current->getName() << std::endl;
    uint8_t x, y;
    std::cout << "x? > ";
    std::cin >> x;
    std::cout << "y? > ";
    std::cin >> y;
    if (current)
    {
        if (players[0] && players[0]->getPlayer() == current)
            players[0]->sendPlay(x, y);
        else if (players[1] && players[1]->getPlayer() == current)
            players[1]->sendPlay(x, y);
    }

    //should not happen
    if (!current)
        std::cout << "/!\\ no current player" << std::endl;
    if (!players[0] || !players[1])
        std::cout << "/!\\ not enough players" << std::endl;
}
