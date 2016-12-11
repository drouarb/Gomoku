//
// Created by lewis_e on 28/10/16.
//

#include <testGUI.hh>
#include <Helpers/History.hh>
#include "Core.hh"
#include "Graph.hpp"
#include "Referee.hpp"
#include "CoreOberser.hh"
#include "Human.hh"
#include "AI.hh"

Core::Core::Core()
{
    History::getInstance();

    // rules
    uniqueRules.push_back(std::list<RuleID>());
    uniqueRules.back().push_back(TIME_10MS);
    uniqueRules.back().push_back(TIME_20MS);
    uniqueRules.back().push_back(TIME_50MS);
    uniqueRules.back().push_back(TIME_200MS);
    uniqueRules.back().push_back(TIME_1S);
    rules.insert(std::pair<RuleID, Rule>(DOUBLE_THREE, Rule(RuleToString.at(DOUBLE_THREE), false)));
    rules.insert(std::pair<RuleID, Rule>(BREAKABLE_FIVE, Rule(RuleToString.at(BREAKABLE_FIVE), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_10MS, Rule(RuleToString.at(TIME_10MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_20MS, Rule(RuleToString.at(TIME_20MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_50MS, Rule(RuleToString.at(TIME_50MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_200MS, Rule(RuleToString.at(TIME_200MS), true)));
    rules.insert(std::pair<RuleID, Rule>(TIME_1S, Rule(RuleToString.at(TIME_1S), false)));

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
  //  History::close();
  //  History::getInstance();
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
    gui->feedBoard(referee->getBoardCopy());
    players[0]->setScore(0);
    players[1]->setScore(0);
    referee->feedRules(rules);
    int player_index = 0;
    while (referee->getWinner() == NOPLAYER && !gui->getObs()->getStop() && gui->getICoreObserver()->gameIsRunning())
    {
        letPlayerPlay(player_index);
        player_index = !player_index;
    }
    stopNodeCache();
    if (gui->getICoreObserver()->gameIsRunning())
    {
        History::getInstance()->writeWinner(TEAMNAME(referee->getWinner()));
        gui->endGame(TEAMNAME(referee->getWinner()));
    }
    else
    {
        gui->endGame("NO ONE");
        History::getInstance()->writeWinner("NOONE");
    }
    History::close();
}

void Core::Core::setRule(const std::string &rulename, bool on)
{
    for (auto& rule : rules)
    {
        if (rule.second.name == rulename)
        {
            rule.second.on = on;
            History::getInstance()->writeRule(rule.first, true);
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
                if (on == false)
                {
                    rules[uniqueRule].on = true;
                    return;
                }
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
    players[index] = new Players::AIPlayer(name, TEAMOF(index));
    players[index]->init(referee);
    gui->registerPlayer(players[index]);
    setAITime();
}

void Core::Core::letPlayerPlay(int index)
{
    gui->setCurrentPlayer(players[index]);
    referee->setPlayer(TEAMOF(index));
    players[index]->play();
    gui->feedBoard(referee->getBoardCopy());
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
    referee->feedRules(rules);
    setAITime();
}

Core::Core::Core(const std::string &path) {
    // rules
    uniqueRules.push_back(std::list<RuleID>());
    uniqueRules.back().push_back(TIME_10MS);
    uniqueRules.back().push_back(TIME_20MS);
    uniqueRules.back().push_back(TIME_50MS);
    uniqueRules.back().push_back(TIME_200MS);
    uniqueRules.back().push_back(TIME_1S);
    rules.insert(std::pair<RuleID, Rule>(DOUBLE_THREE, Rule(RuleToString.at(DOUBLE_THREE), false)));
    rules.insert(std::pair<RuleID, Rule>(BREAKABLE_FIVE, Rule(RuleToString.at(BREAKABLE_FIVE), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_10MS, Rule(RuleToString.at(TIME_10MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_20MS, Rule(RuleToString.at(TIME_20MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_50MS, Rule(RuleToString.at(TIME_50MS), false)));
    rules.insert(std::pair<RuleID, Rule>(TIME_200MS, Rule(RuleToString.at(TIME_200MS), true)));
    rules.insert(std::pair<RuleID, Rule>(TIME_1S, Rule(RuleToString.at(TIME_1S), false)));

    // referee
    referee = new Referee();

    // players
    players[0] = NULL;
    players[1] = NULL;

    // gui
    gui = new GUI::testGUI(path);
    feedRules();
    gui->init(new GUI::CoreObserver(*this)); //thread now goes to gui
}

void Core::Core::setAITime()
{
    int time = 1000;
    if (rules[TIME_10MS].on)
        time = 10;
    if (rules[TIME_20MS].on)
        time = 20;
    if (rules[TIME_50MS].on)
        time = 50;
    if (rules[TIME_200MS].on)
        time = 200;
    if (rules[TIME_1S].on)
        time = 1000;
    if (players[0] && dynamic_cast<Players::AIPlayer *>(players[0]))
        dynamic_cast<Players::AIPlayer*>(players[0])->setTime(time);
    if (players[1] && dynamic_cast<Players::AIPlayer *>(players[1]))
        dynamic_cast<Players::AIPlayer*>(players[1])->setTime(time);
}

void Core::Core::stopNodeCache()
{
    if (players[0] && players[1] && (dynamic_cast<Players::AIPlayer*>(players[0]) || dynamic_cast<Players::AIPlayer*>(players[1])))
        AI::NodeCache::getInstance(NULL)->stop();
}
