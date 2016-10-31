
#include "Ai.hh"

using namespace Players;

Ai::Ai(std::string &name) : name(name)
{ }

const std::string &Ai::getName() const
{
    return (name);
}

bool Ai::play()
{
    return false;
}

bool Ai::init(Core::IReferee &referee)
{
    return false;
}

bool Ai::tryPlay(uint8_t x, uint8_t y)
{
    return false;
}

Ai::~Ai()
{

}
