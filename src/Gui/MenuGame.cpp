//
// Created by celeriy on 02/11/16.
//

#include <list>
#include <Gui/Graph.hpp>
#include "MenuGame.hh"
#include "Button.hpp"
#include "Layer.hh"
#include "IPlayer.hh"

using namespace GUI;


void GUI::MenuGame::loadAsset()
{
    gui->loadImage("./ressource/rules.png", "Rules");
    gui->loadImage("./ressource/Player1.png", "Player1");
    gui->loadImage("./ressource/Player2.png", "Player2");
    gui->loadImage("./ressource/board.png", "Board");
    gui->loadImage("./ressource/white.png", "White");
    gui->loadImage("./ressource/white_selected.png", "White_selected");
    gui->loadImage("./ressource/black_selected.png", "Black_selected");
    gui->loadImage("./ressource/black.png", "Black");
    gui->loadImage("./ressource/Oneplayer.png", "Oneplayer");
    gui->loadImage("./ressource/Twoplayers.png", "Twoplayers");
    gui->loadImage("./ressource/Iaplayers.png", "Iaplayers");
    gui->loadImage("./ressource/background.png", "Background");
    gui->setPolice("./ressource/PTC55F.ttf", 35);
    gui->loadImage("./ressource/checked.png", "Checked");
    gui->loadImage("./ressource/Launch.png", "Launch");
    gui->loadImage("./ressource/white_stones.png", "WhiteStones");
    gui->loadImage("./ressource/black_stones.png", "BlackStones");
    gui->loadImage("./ressource/unchecked.png", "Unchecked");
    gui->changeOpacity("Checked", 255, 255, 255);
    gui->changeOpacity("Rules", 255, 255, 255);
    gui->changeOpacity("BlackStones", 255, 255, 255);
    gui->changeOpacity("Player1", 255, 255, 255);
    gui->changeOpacity("Player2", 255, 255, 255);
    gui->changeOpacity("Launch", 255, 255, 255);
    gui->changeOpacity("Unchecked", 255, 255, 255);
    this->height = 1020;
    this->witdh = 1920;
}


void GUI::MenuGame::loadButton()
{
    t_size buff = gui->getSizePicture("Board");
    IButton *board = new Button<MenuGame>(buff.dimx, buff.dimy, 460, 0, "Board", this, &MenuGame::sendPlay);
    board->setTypButton(BOARD);
    buff = gui->getSizePicture("Checked");

    Graph *g = dynamic_cast<Graph *>(this->gui);
    std::list<std::pair<std::string, bool>> rules = g->rules;
    IButton *buffer;
    int y = 0;
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        buffer = new Button<MenuGame>(buff.dimx, buff.dimy, board->getStartx() + board->getWitdh() + 10, 100 + y,
                                      it->first, this, &MenuGame::sendRule);
        buffer->setDataHandler(buffer);
        buffer->setTypButton(CHECKBOX);
        if (it->second == false)
            buffer->setStats(UNCHECKED);
        else
            buffer->setStats(CHECKED);
        addButtons(buffer);
        y += buff.dimy;
    }
    buff = gui->getSizePicture("White");
    IButton *White = new Button<MenuGame>(buff.dimx, buff.dimy, 100, 600, "White", this, &MenuGame::setSomething);
    White->setTypButton(SELECTBOX);
    IButton *Black = new Button<MenuGame>(buff.dimx, buff.dimy, White->getWitdh() + White->getStartx() + 100,
                                          White->getStarty(), "Black", this, &MenuGame::setSomething);
    Black->setTypButton(SELECTBOX);
    Black->setStats(SELECTED);
    buff = gui->getSizePicture("Oneplayer");
    IButton *Oneplayer = new Button<MenuGame>(buff.dimx, buff.dimy, 100,
                                              White->getStarty() + White->getHeight() + 10, "Oneplayer", this,
                                              &MenuGame::playGameOnePlayers);
    Oneplayer->setTypButton(STARTGAME);
    IButton *Twoplayer = new Button<MenuGame>(buff.dimx, buff.dimy, Oneplayer->getStartx(),
                                              Oneplayer->getStarty() + Oneplayer->getHeight() + 10, "Twoplayers", this,
                                              &MenuGame::playGameTwoPlayers);
    Twoplayer->setTypButton(STARTGAME);
    IButton *Iaplayers = new Button<MenuGame>(buff.dimx, buff.dimy, Oneplayer->getStartx(),
                                              Twoplayer->getStarty() + Twoplayer->getHeight() + 10, "Iaplayers", this,
                                              &MenuGame::playGameIa);
    Iaplayers->setTypButton(STARTGAME);
    addButtons(board);
    addButtons(Iaplayers);
    addButtons(Twoplayer);
    addButtons(Oneplayer);
    addButtons(White);
    addButtons(Black);
}

void GUI::MenuGame::aff()
{
    gui->addToScreen("Background", 0, 0);
    affButtons();
    std::vector<ILayer *> f = getListLayer();
    std::vector<ILayer *>::iterator it = f.begin();
    GameBoard_t board = dynamic_cast<GUI::Graph *>(this->gui)->board;
    int x = 0;
    int y = 0;
    while (it != f.end())
    {
        gui->addToScreen((*it)->getName(), (*it)->getStartx(), (*it)->getStarty());
        it++;
    }
    if (board != NULL)
        for (int i = 0; i < BOARDSIZE; i++)
        {
            if (board[i] == WHITE)
                gui->addToScreen("WhiteStones", calcx(x), calcy(y));
            if (board[i] == BLACK)
                gui->addToScreen("BlackStones", calcx(x), calcy(y));
            x++;
            if (x == 19)
            {
                y++;
                x = 0;
            }
        }
    gui->popupString();
}

void MenuGame::affButtons()
{
    std::vector<IButton *> f = getListButton();
    std::vector<IButton *>::iterator it = f.begin();
    Graph *g = dynamic_cast<Graph *>(this->gui);
    std::list<std::pair<std::string, bool>> rules = g->rules;
    while (it != f.end())
    {

        if ((*it)->getType() == CHECKBOX)
        {
            for (std::list<std::pair<std::string, bool> >::iterator it2 = rules.begin();
                 it2 != rules.end(); ++it2)
            {
                if (it2->first == (*it)->getName())
                {
                    if (it2->second == true && (*it)->getStats() != CHECKED)
                        (*it)->setStats(CHECKED);
                    if (it2->second == false && (*it)->getStats() != UNCHECKED)
                        (*it)->setStats(UNCHECKED);
                    break;
                }
            }

            if ((*it)->getStats() == CHECKED)
                gui->addToScreen("Checked", (*it)->getStartx(), (*it)->getStarty());
            else
                gui->addToScreen("Unchecked", (*it)->getStartx(), (*it)->getStarty());
            gui->addTextToScreen((*it)->getName(), (*it)->getStartx() + (*it)->getWitdh(),
                                 (*it)->getStarty() + (*it)->getHeight() / 3);
        } else if ((*it)->getType() == SELECTBOX)
        {
            if ((*it)->getStats() == SELECTED)
                gui->addToScreen((*it)->getName() + "_selected", (*it)->getStartx(), (*it)->getStarty());
            else
                gui->addToScreen((*it)->getName(), (*it)->getStartx(), (*it)->getStarty());

        } else
        {
            gui->addToScreen((*it)->getName(), (*it)->getStartx(), (*it)->getStarty());
        }
        it++;
    }
}

void GUI::MenuGame::setSomething(void *)
{

}

MenuGame::MenuGame(IGUI *gui)
{
    this->gui = gui;
    loadAsset();
    loadButton();
    loadLayer();
    aff();
}

void MenuGame::loadLayer()
{
    t_size buff = gui->getSizePicture("Rules");
    ILayer *Rules = new Layer(gui->getSizePicture("Board").dimx + 500, 0, buff.dimx, buff.dimy, "Rules");
    ILayer *Lauch = new Layer(100, 500, buff.dimx, buff.dimy, "Launch");
    buff = gui->getSizePicture("Player1");
    ILayer *Player1 = new Layer(0, 0, buff.dimx, buff.dimy, "Player1");
    ILayer *Player2 = new Layer(0, buff.dimy, buff.dimx, buff.dimy, "Player2");
    addLayer(Player1);
    addLayer(Player2);
    addLayer(Rules);
    addLayer(Lauch);
}

void MenuGame::sendRule(void *button)
{
    IButton *but = static_cast<IButton *>(button);
    if (but->getStats() == CHECKED)
        this->gui->getICoreObserver()->setRule(but->getName(), false);
    else
        this->gui->getICoreObserver()->setRule(but->getName(), true);
}

void MenuGame::playGameOnePlayers()
{
    this->gui->getICoreObserver()->playGame(GamePlayers::ONEPLAYER);
}

void MenuGame::playGameTwoPlayers()
{
    this->gui->getICoreObserver()->playGame(GamePlayers::TWOPLAYERS);
}

void MenuGame::playGameIa()
{
    this->gui->getICoreObserver()->playGame(GamePlayers::TWOAIS);
}

void MenuGame::sendPlay()
{
    t_size *last = (dynamic_cast<GUI::Graph *>(gui))->last;
    Players::IPlayer *player = (dynamic_cast<GUI::Graph *>(gui))->current;
    IPlayerObserver *iob1 = (dynamic_cast<GUI::Graph *>(gui))->players[0];
    uint8_t x = invcalcx(last->dimx);
    uint8_t y = invcalcy(last->dimy);
    if (iob1 != NULL && iob1->getPlayer() == player)
        iob1->sendPlay(x, y);
    iob1 = dynamic_cast<IPlayerObserver *>((dynamic_cast<GUI::Graph *>(gui))->players[1]);
    if (iob1 != NULL && iob1->getPlayer() == player)
        iob1->sendPlay(x, y);
}

