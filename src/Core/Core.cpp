//
// Created by lewis_e on 28/10/16.
//

#include "Core.hh"
//#include "GUImas.hh"
#include "Referee.hh"

Core::Core::Core()
{
    // rules
    uniqueRules.push_back(std::list<std::string>());
    rules.push_back(std::pair<std::string, bool>("Triple three", false));
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
    //TO DO: observer
    //gui = new GUI::GUImas();
    //TO DO: init
    //gui->feedRules(rules);
    //gui->feedBoard(referee->getBoardRef());
}

Core::Core::~Core()
{ }

void Core::Core::playGame(::Core::GamePlayers player_config)
{
    mutex.lock();

    mutex.unlock();
}

void Core::Core::setRule(const std::string &rule, bool on)
{
    mutex.lock();

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
        for (std::list<std::pair<std::string, bool> >::iterator rule_it = rules.begin();
             rule_it != rules.end(); ++rule_it)
        {
            if (list_it->back() == rule_it->first && rule_it->first != rule)
            {
                rule_it->second = false;
            }
        }
    }

    sendRules();

    mutex.unlock();
}

void Core::Core::sendRules()
{
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        //gui->feedRules(rules);
    }
}
