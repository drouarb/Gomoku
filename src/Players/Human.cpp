
#include "Human.hh"

using namespace Players;

Humain::Humain(std::string & Name)
{
this->name = Name;
}

const std::string &Humain::getName() const
{
    return this->name;
}

bool Humain::play()
{
    return false;
}

bool Humain::init(Core::IReferee & referee1)
{
    this->referee = &referee1;
    return true;
}

bool Humain::tryPlay(uint8_t x, uint8_t y)
{
    return false;
}

Humain::~Humain()
{

}
