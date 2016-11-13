
#include "Human.hh"

using namespace Players;
using namespace GUI;

const std::string &Humain::getName() const
{
    return this->name;
}

bool Humain::play()
{
    this->handle->prompt();
    return true;
}

bool Humain::init(Core::IReferee * referee1)
{
    this->referee = referee1;
    return true;
}

bool Humain::tryPlay(uint8_t x, uint8_t y)
{
    if (referee->tryPlay(x, y) == true)
    return true;
    else
    {
        this->handle->showError(std::string("Forbidden"));
        this->handle->prompt();
        return false;
    }
}

Humain::~Humain()
{

}

Humain::Humain(std::string &Name, GUI::IUIHandle *iuiHandle)
{
    this->name = Name;
    this->handle = iuiHandle;
}

void Humain::setScore(int score)
{
    this->score = score;
}

int Humain::getScore()
{
    return this->score;
}

std::ostream &operator<<(std::ostream &ostream, IPlayer *player) {
    ostream << player->getName() << " : " << player->getScore();
    return ostream;
}