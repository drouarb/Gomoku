
#include <AI/MonteCarlo.hh>
#include "AI.hh"

using namespace Players;

AIPlayer::AIPlayer(std::string &name, Team team) {
    this->name = name;
    this->team = team;
}

AIPlayer::~AIPlayer() {

}

const std::string &AIPlayer::getName() const {
    return (name);
}

bool AIPlayer::init(Core::IReferee *referee) {
    this->referee = referee;
    this->nodeCache = AI::NodeCache::getInstance(referee);
    std::cout << "AI init done" << std::endl;
    return true;
}

bool AIPlayer::play() {
    std::cout << "AIPLAY" << std::endl;
    nodeCache->getMove(referee, 200);
    return false;
}

void AIPlayer::setIBoardOperator(Core::BoardOperator *op) {
    this->boardOperator = op;
}

void AIPlayer::setScore(int score) {
    this->score = score;
}

int AIPlayer::getScore() {
    return this->score;
}
