#include "Referee.hh"

Core::Referee::Referee()
{
  board = new char[BOARDSIZE];
  initialize();
}

Core::Referee::~Referee()
{
  delete board;
}

void		Core::Referee::initialize()
{
  int		i;

  i = 0;
  player = NOPLAYER;
  winner = NOPLAYER;
  boardOp = new BoardOperator;
  while (i < BOARDSIZE)
    {
      board[i] = Team::NOPLAYER;
      ++i;
    }
  stats.erase(stats.begin(), stats.end());
  stats.push_back({Core::Team::WHITE, 0});
  stats.push_back({Core::Team::BLACK, 0});
}

GameBoard_t	Core::Referee::getBoardCopy()
{
  int		i;
  GameBoard_t	newBoard;

  while (i < BOARDSIZE)
    newBoard[i] = board[i++];
  return (newBoard);
}

const GameBoard_t&	Core::Referee::getBoardRef()
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
  if (winner != NOPLAYER)
    return (false);
  if (boardOp->checkPos(x, y) != NOPLAYER)
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

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y, GameBoard_t *nboard)
{
  boardOp->feed(nboard);
<<<<<<< HEAD
  if (boardOp->checkPos(x, y) != Core::Team::NOPLAYER)
=======
  if (winner != NOPLAYER)
    return (false);
  if (boardOp->checkPos(x, y) != NOPLAYER)
>>>>>>> ec931bcf5448788154dde496a27031ef925c9a5e
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

Team	Core::Referee::getWinner() const
{
  return (winner);
}
