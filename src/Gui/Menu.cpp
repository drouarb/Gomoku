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
void Menu::addLayer(ILayer *button)
{
    this->listLayer.push_back(button);
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

void Menu::delLayer(ILayer *button)
{
    std::vector<ILayer *>::iterator it = listLayer.begin();
    if (listLayer.empty() == false)
    {
        while (it != listLayer.end())
        {
            if (*it == button)
            {
                listLayer.erase(it);
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

void Menu::clearListLayer()
{
    this->listLayer.clear();
}


const std::vector<IButton *> &Menu::getListButton() const
{
  return listButton;
}

const std::vector<ILayer *> &Menu::getListLayer() const
{
    return listLayer;
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







