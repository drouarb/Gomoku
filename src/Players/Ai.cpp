
#include "Ai.hh"

using namespace Players;

const std::string &Ai::getName()
{
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
