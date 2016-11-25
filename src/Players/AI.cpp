
#include <AI/MonteCarlo.hh>
#include "AI.hh"

using namespace Players;

AIPlayer::AIPlayer(std::string &name) {
    this->name = name;
}

AIPlayer::~AIPlayer() {

}

const std::string &AIPlayer::getName() const {
    return (name);
}

bool AIPlayer::init(Core::IReferee *referee) {
    this->referee = referee;
    return true;
}

bool AIPlayer::play() {
    AI::MonteCarlo mc(this->referee, this->referee->getPlayer());
    mc.run();
    return false;
}

void AIPlayer::setIBoardOperator(Core::IBoardOperator *op) {
    this->boardOperator = op;
}

void AIPlayer::setScore(int score) {
    this->score = score;
}

int AIPlayer::getScore() {
    return this->score;
}
