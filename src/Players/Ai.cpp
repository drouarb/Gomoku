
#include "Ai.hh"

using namespace Players;

Ai::Ai(std::string &name)
{
    this->name = name;
}

const std::string &Ai::getName() const
{
    return (name);
}

bool Ai::play()
{
    return false;
}

bool Ai::init(Core::IReferee *referee)
{
    this->referee = referee;
    return true;
}

bool Ai::tryPlay(uint8_t x, uint8_t y)
{
    if (this->referee->tryPlay(x, y) == true)
        return true;
    return false;
}

Ai::~Ai()
{

}

void Ai::setIBoardOperator(Core::IBoardOperator *op)
{
    this->boardOperator = op;
}
