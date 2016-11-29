#include "Referee.hpp"
#include <string.h>

Core::Referee::Referee()
{
  initialize();
}


Core::Referee::Referee(const Referee & other) :
        boardOp(new BoardOperator(static_cast<const BoardOperator &>(*other.boardOp))), stats(other.stats),
        player(other.player), winner(other.winner), rRules(other.rRules)
{ }

Core::Referee::~Referee()
{ }

void		Core::Referee::initialize()
{
  player = NOPLAYER;
  winner = NOPLAYER;
  boardOp = new BoardOperator;
  stats.insert(std::pair<Team, statPlayer>(Team::WHITE, statPlayer()));
  stats.insert(std::pair<Team, statPlayer>(Team::BLACK, statPlayer()));
}

GameBoard_t	Core::Referee::getBoardCopy()
{
  GameBoard_t	newBoard;

    newBoard = new Team[BOARDSIZE];
    for (int y = 0; y < XBOARD; y++)
    {
        for (int x = 0; x < XBOARD; x++)
        {
            newBoard[y * XBOARD + x] = boardOp->boardAt(x, y);
        }
    }
  return (newBoard);
}

void		Core::Referee::setPlayer(Team nplayer)
{
  player = nplayer;
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y)
{
  if (winner != NOPLAYER)
    return (false);
  if (boardOp->boardAt(x, y) != NOPLAYER)
    return (false);
  if ((*rRules)[DOUBLE_THREE].on == true)
    if (boardOp->checkFreeDoubleThree(player, x, y) == true)
      return (false);
  stats[player].eaten += boardOp->applyEat(player, x, y);
  boardOp->ForceupdateBoard(player, x, y);
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if ((*rRules)[BREAKABLE_FIVE].on == true)
    {
      if (boardOp->checkfiveWinBreak(player) == true)
	winner = player;
    }
  else
    {
      if (boardOp->checkfiveWinNoBreak(player) == true)
	winner = player;
    }
  return (true);
}

bool		Core::Referee::tryPlay(boardPos_t pos)
{
  uint8_t	x;
  uint8_t	y;

  x = pos % XBOARD;
  y = pos / XBOARD;
  if (winner != NOPLAYER)
    return (false);
  if (boardOp->boardAt(x, y) != NOPLAYER)
    return (false);
  if ((*rRules)[DOUBLE_THREE].on == true)
    if (boardOp->checkFreeDoubleThree(player, x, y) == true)
      return (false);
  stats[player].eaten += boardOp->applyEat(player, x, y);
  boardOp->ForceupdateBoard(player, x, y);
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if ((*rRules)[BREAKABLE_FIVE].on == true)
    {
      if (boardOp->checkfiveWinBreak(player) == true)
	winner = player;
    }
  else
    {
      if (boardOp->checkfiveWinNoBreak(player) == true)
	winner = player;
    }
  player = (player == Team::WHITE) ? Team::BLACK : Team::WHITE;
  return (true);
}

void		Core::Referee::feedRules(std::map<RuleID, Rule> & rules)
{
  rRules = &rules;
}

Team	Core::Referee::getWinner() const
{
  return (winner);
}

uint8_t	Core::Referee::getTeamEat(Team player)
{
  return (stats[player].eaten * 2);
}

Core::IBoardOperator *Core::Referee::getBoOp() const
{
  return (boardOp);
}

Team Core::Referee::getPlayer() const
{
  return (player);
}

Core::IReferee *Core::Referee::clone() {
  return new Referee(*this);
}
