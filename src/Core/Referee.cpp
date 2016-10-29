#include "Referee.hh"

Core::Referee::Referee()
{
  initialize();
}

Core::Referee::~Referee()
{
}

void		Core::Referee::initialize()
{
  int		i;

  i = 0;
  player = Core::Team::NOPLAYER;
  winner = Core::Team::NOPLAYER;
  boardOp = new BoardOperator;
  while (i < BOARDSIZE)
    {
      board[i] = 0;
      ++i;
    }
}

Core::GameBoard_t	Core::Referee::getBoardCopy()
{
  int		i;
  Core::GameBoard_t	newBoard;

  while (i < BOARDSIZE)
    newBoard[i] = board[i++];
  return (newBoard);
}

const Core::GameBoard_t&	Core::Referee::getBoardRef()
{
  return (board);
}

void		Core::Referee::setPlayer(Team nplayer)
{
  player = nplayer;
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y)
{
  boardOp->feed(&board);
  if (winner != Core::Team::NOPLAYER)
    return (false);
  if (boardOp->checkPos(x, y) != Core::Team::NOPLAYER)
    return (false);
  if (boardOp->checkFreeDoubleThree(player, x, y) == true)
    return (false);
  boardOp->applyEat(player, x, y);
  if (boardOp->checkfiveWin(player) == true)
    winner = player;
  boardOp->ForceupdateBoard(player, x, y);
  return (false);
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y, Core::GameBoard_t *nboard)
{
  boardOp->feed(nboard);
  if (winner != Core::Team::NOPLAYER)
    return (false);
  if (boardOp->checkPos(x, y) != Core::Team::NOPLAYER)
    return (false);
  if (boardOp->checkFreeDoubleThree(player, x, y) == true)
    return (false);
  boardOp->applyEat(player, x, y);
  if (boardOp->checkfiveWin(player) == true)
    winner = player;
  boardOp->ForceupdateBoard(player, x, y);
  return (false);
}

const Core::IBoardOperator *Core::Referee::getBoardOperator()
{
  return (boardOp);
}

Core::Team	Core::Referee::getWinner() const
{
  return (winner);
}
