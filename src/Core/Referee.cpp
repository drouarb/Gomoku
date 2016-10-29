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
  stats.erase(stats.begin(), stats.end());
  stats.push_back({Core::Team::WHITE, 0});
  stats.push_back({Core::Team::BLACK, 0});
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
  stats[player - 1].eaten += boardOp->applyEat(player, x, y);
  if (stats[player - 1].eaten >= EATWIN)
    winner = player;
  if (boardOp->checkfiveWin(player) == true)
    winner = player;
  boardOp->ForceupdateBoard(player, x, y);
  return (false);
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y, Core::GameBoard_t *nboard)
{
  boardOp->feed(nboard);
  if (boardOp->checkPos(x, y) != Core::Team::NOPLAYER)
    return (false);
  if (boardOp->checkFreeDoubleThree(player, x, y) == true)
    return (false);
  //boardOp->ForceupdateBoard(player, x, y);
  return (true);
}

#warning "je suis pas d'accord avec cette méthode en bas"

const Core::IBoardOperator *Core::Referee::getBoardOperator()
{
  return (boardOp);
}

Core::Team	Core::Referee::getWinner() const
{
  return (winner);
}
