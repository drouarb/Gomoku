//
// Created by celeriy on 02/11/16.
//

#include "MenuGame.hh"
#include "Button.hpp"
#include "Layer.hh"

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
    gui->setPolice("./ressource/PTC55F.ttf", 45);
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
    IButton *board = new Button<MenuGame>(buff.dimx, buff.dimy, 460, 0, "Board", this, &MenuGame::setSomething);
    board->setTypButton(BOARD);
    buff = gui->getSizePicture("Checked");
    IButton *doubleThree = new Button<MenuGame>(buff.dimx, buff.dimy, board->getStartx() + board->getWitdh() + 10, 700,
                                                "DoubleThree", this, &MenuGame::setSomething);
    doubleThree->setTypButton(CHECKBOX);
    doubleThree->setStats(UNCHECKED);
    IButton *Cassable = new Button<MenuGame>(buff.dimx, buff.dimy, board->getStartx() + board->getWitdh() + 10,
                                             doubleThree->getStarty() + doubleThree->getHeight() + 20, "5 Unbreakable",
                                             this, &MenuGame::setSomething);
    Cassable->setTypButton(CHECKBOX);
    Cassable->setStats(UNCHECKED);
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
                                              &MenuGame::setSomething);
    Oneplayer->setTypButton(STARTGAME);
    IButton *Twoplayer = new Button<MenuGame>(buff.dimx, buff.dimy, Oneplayer->getStartx(),
                                              Oneplayer->getStarty() + Oneplayer->getHeight() + 10, "Twoplayers", this,
                                              &MenuGame::setSomething);
    Twoplayer->setTypButton(STARTGAME);
    IButton *Iaplayers = new Button<MenuGame>(buff.dimx, buff.dimy, Oneplayer->getStartx(),
                                              Twoplayer->getStarty() + Twoplayer->getHeight() + 10, "Iaplayers", this,
                                              &MenuGame::setSomething);
    Iaplayers->setTypButton(STARTGAME);
    addButtons(board);
    addButtons(Cassable);
    addButtons(doubleThree);
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
    while (it != f.end())
    {
        gui->addToScreen((*it)->getName(), (*it)->getStartx(), (*it)->getStarty());
        it++;
    }
    gui->popupString();
}

void MenuGame::affButtons() const
{
    std::vector<IButton *> f = getListButton();
    std::vector<IButton *>::iterator it = f.begin();
    while (it != f.end())
    {

        if ((*it)->getType() == CHECKBOX)
        {
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
    ILayer *Rules = new Layer(gui->getSizePicture("Board").dimx + 500, 600, buff.dimx, buff.dimy, "Rules");
    ILayer *Lauch = new Layer(100, 500, buff.dimx, buff.dimy, "Launch");
    buff = gui->getSizePicture("Player1");
    ILayer *Player1 = new Layer(0, 0, buff.dimx, buff.dimy, "Player1");
    ILayer *Player2 = new Layer(this->witdh - buff.dimx, 0, buff.dimx, buff.dimy, "Player2");
   addLayer(new Layer(700,400, buff.dimx, buff.dimy, "WhiteStones"));
    addLayer(Player1);
    addLayer(Player2);
    addLayer(Rules);
    addLayer(Lauch);
}
