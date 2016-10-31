//
// Created by lewis_e on 28/10/16.
//

#include "Core.hh"
#include "GUImas.hh"
#include "Referee.hh"
#include "CoreOberser.hh"
#include "Human.hh"
#include "Ai.hh"

Core::Core::Core()
{
    // rules
    uniqueRules.push_back(std::list<std::string>());
    rules.push_back(std::pair<std::string, bool>("Double three", false));
    rules.push_back(std::pair<std::string, bool>("Breakable five", false));
    rules.push_back(std::pair<std::string, bool>("Timed AI: 10 ms", false));
    uniqueRules.back().push_back(rules.back().first);
    rules.push_back(std::pair<std::string, bool>("Timed AI: 20 ms", false));
    uniqueRules.back().push_back(rules.back().first);
    rules.push_back(std::pair<std::string, bool>("Timed AI: 50 ms", false));
    uniqueRules.back().push_back(rules.back().first);

    // referee
    referee = new Referee();

    // players
    players[0] = NULL;
    players[1] = NULL;

    // gui
    gui = new GUI::GUImas();
    gui->feedRules(rules);
    gui->init(new GUI::CoreObserver(*this)); //thread now goes to gui
}

Core::Core::~Core()
{ }

void Core::Core::playGame(GamePlayers player_config)
{
    if (player_config != TWOAIS)
        createPlayerHuman(0);
    else
        createPlayerAI(0);
    if (player_config == TWOPLAYERS)
        createPlayerHuman(1);
    else
        createPlayerAI(1);

    referee->initialize();
    gui->startGame();
    gui->feedBoard(referee->getBoardRef());

    int player_index = 0;
    while (referee->getWinner() == NOPLAYER)
    {
        letPlayerPlay(player_index);
        player_index = !player_index;
    }

    gui->endGame(TEAMNAME(referee->getWinner()));
}

void Core::Core::setRule(const std::string &rule, bool on)
{
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        if (it->first == rule)
        {
            it->second = on;
            break;
        }
    }

    for (std::list<std::list<std::string > >::iterator list_it = uniqueRules.begin();
         list_it != uniqueRules.end(); ++list_it)
    {
        for (std::list<std::string >::iterator elem_it = list_it->begin();
             elem_it != list_it->end(); ++elem_it)
        {
            for (std::list<std::pair<std::string, bool> >::iterator rule_it = rules.begin();
                 rule_it != rules.end(); ++rule_it)
            {
                if (*elem_it == rule_it->first && rule_it->first != rule)
                {
                    rule_it->second = false;
                }
            }
        }
    }

    gui->feedRules(rules);
}

void Core::Core::destroyPlayer(int index)
{
    if (players[index] != NULL)
    {
        if (dynamic_cast<Players::IHumain *>(players[index]) != NULL)
            gui->unregisterPlayer(players[index]);
        delete (players[index]);
        players[index] = NULL;
    }
}

void Core::Core::createPlayerHuman(int index)
{
    destroyPlayer(index);
    std::string name = TEAMNAME(TEAMOF(index));
    name += " player";
    players[index] = new Players::Humain(name);
    gui->registerPlayer(players[index]);
}

void Core::Core::createPlayerAI(int index)
{
    destroyPlayer(index);
    std::string name = TEAMNAME(TEAMOF(index));
    name += " A.I.";
    players[index] = new Players::Ai(name);
}

void Core::Core::letPlayerPlay(int index)
{
    gui->setCurrentPlayer(players[index]->getName());
    referee->setPlayer(TEAMOF(index));
    players[index]->play();
    gui->feedBoard(referee->getBoardRef());
}