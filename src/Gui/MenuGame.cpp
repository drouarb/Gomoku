//
// Created by celeriy on 02/11/16.
//

#include "MenuGame.hh"

void GUI::MenuGame::loadAsset()
{
    gui->loadImage("./ressource/board.png", "Board");
    gui->loadImage("./ressource/background.png", "Background");
}

void GUI::MenuGame::loadButton()
{
}

void GUI::MenuGame::aff()
{
    gui->addToScreen("Background", 0 , 0);
    gui->addToScreen("Board", 480, 0);
}

void GUI::MenuGame::setSomething(void *)
{

}

MenuGame::MenuGame(IGUI *gui)
{
  this->gui = gui;
    loadAsset();
    aff();
}
