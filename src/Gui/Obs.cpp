//
// Created by celeri_y on 4/18/16.
//

#include <iostream>
#include "Obs.hpp"

using namespace GUI;

void Obs::notify(int x, int y)
{
  std::vector<IMenu*>::iterator it = listMenu.begin();
  std::vector<IButton*>::iterator itButons;
   bool find = false;
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
		find = true;
	    }
	  itButons++;
	}
      if (find == true)
	   break;
      it++;
    }
  it = listMenu.begin();
  while (it != listMenu.end())
  {
      (*it)->loadButton();
      (*it)->aff();
    it++;
  }
}

Obs::Obs()
{
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







