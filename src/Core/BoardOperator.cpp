#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator()
{
}

Core::BoardOperator::~BoardOperator()
{
}

void		Core::BoardOperator::feed(GameBoard_t *nboard)
{
  board = nboard;
}

bool		Core::BoardOperator::checkFreeDoubleThree(Team player, uint8_t x, uint8_t y)
{
  return (false);
}

std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getFreeDoubleThreePos(Team player)
{
}

bool              Core::BoardOperator::checkEatPlayer(Team player, uint8_t x, uint8_t y)
{
  return (false);
}

std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> Core::BoardOperator::getEatPos(Team player)
{
}

bool              Core::BoardOperator::checkfiveWin(Team player)
{
  return (false);
}


std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getXPossible(uint8_t numberPiece, Team player)
{
}

bool              Core::BoardOperator::checkBreakable(Team player)
{
  return (false);
}

Team		Core::BoardOperator::checkPos(uint8_t x, uint8_t y)
{
  return (board[y * XBOARD + x]);
}

uint8_t			Core::BoardOperator::applyEat(Team player, uint8_t x, uint8_t y)
{

}

void			Core::BoardOperator::ForceupdateBoard(Team player, uint8_t x, uint8_t y)
{

}
