#include "Referee.hh"
using namespace Core;

Core::Referee::Referee()
{
  int		i;
  board[i] = 0;
}

Core::Referee::~Referee()
{
}

GameBoard_t	getBoardCopy()
{
  int		i;
  GameBoard_t	newBoard;

  while (i < BOARDSIZE)
    newBoard[i] = board[i++];
  return (newBoard);
}

const GameBoard_t&	Core::Referee::getBoardRef()
{

}

void		Core::Referee::setPlayer(Team player)
{
  
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y)
{

}

bool Referee::tryPlay(uint8_t x, uint8_t y, const GameBoard_t &)
{
    return false;
}

const BoardOperator &Referee::getBoardOperator()
{
}

GameBoard_t Referee::getBoardCopy()
{
    return nullptr;
}
