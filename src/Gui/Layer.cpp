//
// Created by celeriy on 02/11/16.
//

#include "Layer.hh"
using namespace GUI;

Layer::Layer(int startx, int starty, int witdh, int height, const std::string &name)
{
    this->height = height;
    this->startx = startx;
    this->witdh = witdh;
    this->starty = starty;
    this->name = name;
}


const std::string &Layer::getName() const
{
    return this->name;
}

int Layer::getStartx() const
{
    return this->startx;
}

int Layer::getWitdh() const
{
    return this->witdh;
}

int Layer::getHeight() const
{
    return this->height;
}

int Layer::getStarty() const
{
    return this->starty;
}
