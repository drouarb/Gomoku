//
// Created by celeri_y on 4/18/16.
//

#include <iostream>
#include "Obs.hpp"

using namespace GUI;

typeButton Obs::notify(int x, int y)
{
  std::vector<IMenu*>::iterator it = listMenu.begin();
  std::vector<IButton*>::iterator itButons;
   bool find = false;
    typeButton  re;
   std::vector<IButton*> buffButtons;
  if (listMenu.empty() == false)
  while (it != listMenu.end())
    {
       buffButtons = (*it)->getListButton();
      itButons = buffButtons.begin();
      while (itButons != buffButtons.end())
	{
	    if ((*itButons)->checkPos(x, y ) == true)
	    {
	      (*itButons)->execute();
            re = (*itButons)->getType();
		find = true;
	    }
	  itButons++;
        if (find == true)
            break;
    }
      it++;
        if (find == true)
            break;
    }
    actualMenu();
    return re;
}


void Obs::actualMenu()
{
    int i = 0;
    std::vector<IMenu*>::iterator it = listMenu.begin();
    while (it != this->listMenu.end())
  {
       (*it)->aff();
    it++;
  }
}

void Obs::setStop(bool value)
{
    this->stop = value;
}
bool Obs::getStop() const {
    return this->stop;
}
Obs::Obs()
{
    this->stop = false;
}

void Obs::addMenu(IMenu *menu)
{
  this->listMenu.push_back(menu);
}

void Obs::setListMenu(std::vector<IMenu *> &listMnu)
{
  this->listMenu = listMnu;
  std::vector<IMenu*>::iterator it = listMnu.begin();
  std::vector<IButton*> buffButtons = (*it)->getListButton();

}







