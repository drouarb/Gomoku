
#include <Helpers/History.hh>
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
    if (referee->tryPlay(x, y) == true) {
        Core::History::getInstance()->write(y, x, this->getName());
        return true;
    } else {
        Core::History::getInstance()->writeFail(y, x, this->getName());
        this->handle->showError(std::string("Forbidden x: " + std::to_string(x) + "y :" + std::to_string(y)));
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