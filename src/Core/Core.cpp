//
// Created by lewis_e on 28/10/16.
//

#include "Core.hh"
#include "Graph.hpp"
#include "Referee.hpp"
#include "CoreOberser.hh"
#include "Human.hh"
#include "Ai.hh"

Core::Core::Core()
{
    // rules
    uniqueRules.push_back(std::list<RuleID>());
    uniqueRules.back().push_back(TIME_10MS);
    uniqueRules.back().push_back(TIME_20MS);
    uniqueRules.back().push_back(TIME_50MS);
    rules.insert(std::pair<RuleID, Rule>(DOUBLE_THREE, Rule("Double three", false)));
    rules.insert(std::pair<RuleID, Rule>(BREAKABLE_FIVE, Rule("Breakable five", false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_10MS, Rule("Timed AI: 10 ms", false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_20MS, Rule("Timed AI: 20 ms", false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_50MS, Rule("Timed AI: 50 ms", false)));

    // referee
    referee = new Referee();

    // players
    players[0] = NULL;
    players[1] = NULL;

    // gui
    gui = new GUI::Graph();
    feedRules();
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
   // std::cout << player_config << std::endl;
    referee->initialize();
    gui->startGame();
    gui->feedBoard(referee->getBoardRef());
    players[0]->setScore(0);
    players[1]->setScore(1);
    referee->feedRules(rules);
    int player_index = 0;
    while (referee->getWinner() == NOPLAYER && !gui->getObs()->getStop() && gui->getICoreObserver()->gameIsRunning())
    {
        letPlayerPlay(player_index);
          player_index = !player_index;
    }
    if (gui->getICoreObserver()->gameIsRunning())
    gui->endGame(TEAMNAME(referee->getWinner()));
    else
        gui->endGame("NO ONE");
}

void Core::Core::setRule(const std::string &rulename, bool on)
{
    for (auto& rule : rules)
    {
        if (rule.second.name == rulename)
        {
            rule.second.on = on;
            break;
        }
    }

    for (auto& uniqueList : uniqueRules)
    {
        bool uniqueListChanged = false;
        for (auto& uniqueRule : uniqueList)
        {
            if (rules[uniqueRule].name == rulename)
            {
                uniqueListChanged = true;
                break;
            }
        }
        if (uniqueListChanged)
        {
            for (auto &uniqueRule : uniqueList)
            {
                for (auto &rule : rules)
                {
                    if (uniqueRule == rule.first && rule.second.name != rulename)
                    {
                        rule.second.on = false;
                    }
                }
            }
        }
    }

    feedRules();
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
    players[index] = new Players::Humain(name, dynamic_cast<GUI::IUIHandle*>(this->gui));
    players[index]->init(referee);
    gui->registerPlayer(players[index]);
}

void Core::Core::createPlayerAI(int index)
{
    destroyPlayer(index);
    std::string name = TEAMNAME(TEAMOF(index));
    name += " A.I.";
    players[index] = new Players::Ai(name);
    players[index]->init(referee);
}

void Core::Core::letPlayerPlay(int index)
{
    gui->setCurrentPlayer(players[index]);
    referee->setPlayer(TEAMOF(index));
    players[index]->play();
    gui->feedBoard(referee->getBoardRef());
    players[index]->setScore(referee->getTeamEat(TEAMOF(index)));
}

void Core::Core::feedRules()
{
    std::list<std::pair<std::string, bool> > list;

    for (auto& rule : rules)
    {
        list.push_back(std::pair<std::string, bool>(rule.second.name, rule.second.on));
    }
    gui->feedRules(list);
}
