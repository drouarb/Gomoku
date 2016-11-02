//
// Created by celeri_y on 4/17/16.
//

#include <iostream>
#include "Menu.hpp"

using namespace GUI;

void Menu::addButtons(IButton *button)
{
   this->listButton.push_back(button);
}

void Menu::delButton(IButton *button)
{
  std::vector<IButton *>::iterator it = listButton.begin();
  if (listButton.empty() == false)
    {
	while (it != listButton.end())
	  {
	    if (*it == button)
	      {
		listButton.erase(it);
		break;
	      }
	    it++;
	  }

    }
}

void Menu::clearListButton()
{
  this->listButton.clear();
}


const std::vector<IButton *> &Menu::getListButton() const
{
  return listButton;
}

int Menu::getPosx()
{
  return this->posx;
}

int Menu::getPosy()
{
  return  this->posy;
}

int Menu::getHeight()
{
  return this->height;
}

int Menu::getWitdh()
{
  return this->witdh;
}







