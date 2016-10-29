#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator()
{
}

Core::BoardOperator::~BoardOperator()
{
}

void		Core::BoardOperator::feed(Core::GameBoard_t *nboard)
{
  board = nboard;
}

bool		Core::BoardOperator::checkFreeDoubleThree(Core::Team player, uint8_t x, uint8_t y)
{
  return (false);
}

std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getFreeDoubleThreePos(Core::Team player)
{
}

bool              Core::BoardOperator::checkEatPlayer(Core::Team player, uint8_t x, uint8_t y)
{
  return (false);
}

std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> Core::BoardOperator::getEatPos(Core::Team player)
{
}

bool              Core::BoardOperator::checkfiveWin(Core::Team player)
{
  return (false);
}


std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getXPossible(uint8_t numberPiece, Core::Team player)
{
}

bool              Core::BoardOperator::checkBreakable(Core::Team player)
{
  return (false);
}

Core::Team		Core::BoardOperator::checkPos(uint8_t x, uint8_t y)
{
  return (Core::Team::NOPLAYER);
}

uint8_t			Core::BoardOperator::applyEat(Core::Team player, uint8_t x, uint8_t y)
{

}

void			Core::BoardOperator::ForceupdateBoard(Core::Team player, uint8_t x, uint8_t y)
{

}
