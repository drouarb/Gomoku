#include "Referee.hpp"

Core::Referee::Referee()
{
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
  board = new char[BOARDSIZE];
  boardOp = new BoardOperator;
  while (i < BOARDSIZE)
    {
      board[i] = Team::NOPLAYER;
      ++i;
    }
  stats.erase(stats.begin(), stats.end());
  stats.insert(std::pair<Team, statPlayer>(Team::WHITE, statPlayer()));
  stats.insert(std::pair<Team, statPlayer>(Team::BLACK, statPlayer()));
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
  stats[player].eaten += boardOp->applyEat(player, x, y);
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if (boardOp->checkfiveWin(player) == true)
    winner = player;
  boardOp->ForceupdateBoard(player, x, y);
  return (true);
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y, GameBoard_t *nboard)
{
  boardOp->feed(nboard);
  if (boardOp->checkPos(x, y) != NOPLAYER)
    return (false);
  if (boardOp->checkFreeDoubleThree(player, x, y) == true)
    return (false);
  boardOp->ForceupdateBoard(player, x, y);
  return (true);
}

Team	Core::Referee::getWinner() const
{
  return (winner);
}
