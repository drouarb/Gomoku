#include "Referee.hpp"
#include <string.h>

Core::Referee::Referee()
{
  initialize();
}


Core::Referee::Referee(const Referee & other) :
        boardOp(other.boardOp), stats(other.stats),
        player(other.player), winner(other.winner), rRules(other.rRules),
	lastMove(other.lastMove), nbrPlay(other.nbrPlay)
{
}

Core::Referee::~Referee()
{ }

void		Core::Referee::initialize()
{
  player = NOPLAYER;
  winner = NOPLAYER;
  stats.clear();
  nbrPlay = 0;
  lastMove = 0;
  stats.insert(std::pair<Team, statPlayer>(Team::WHITE, statPlayer()));
  stats.insert(std::pair<Team, statPlayer>(Team::BLACK, statPlayer()));
  boardOp = BoardOperator();
}

GameBoard_t	Core::Referee::getBoardCopy()
{
  GameBoard_t	newBoard;

    newBoard = new Team[BOARDSIZE];
    for (int y = 0; y < XBOARD; y++)
    {
        for (int x = 0; x < XBOARD; x++)
        {
            newBoard[y * XBOARD + x] = boardOp.boardAt(x, y);
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
  if (boardOp.boardAt(x, y) != NOPLAYER)
    return (false);
  if ((*rRules)[DOUBLE_THREE].on == true)
    if (boardOp.checkFreeDoubleThree(player, x, y) == true)
      return (false);
  stats[player].eaten += boardOp.applyEat(player, x, y);
  boardOp.ForceupdateBoard(player, x, y);
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if ((*rRules)[BREAKABLE_FIVE].on == true)
    {
      if (boardOp.checkfiveWinBreak(player) == true)
	winner = player;
    }
  else
    {
      if (boardOp.checkfiveWinNoBreak(player) == true)
	winner = player;
    }
  lastMove = x + y * XBOARD;
  ++nbrPlay;
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
  if (boardOp.boardAt(x, y) != NOPLAYER)
    return (false);
  if ((*rRules)[DOUBLE_THREE].on == true)
    if (boardOp.checkFreeDoubleThree(player, x, y) == true)
      return (false);
  stats[player].eaten += boardOp.applyEat(player, x, y);
  boardOp.ForceupdateBoard(player, x, y);
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if ((*rRules)[BREAKABLE_FIVE].on == true)
    {
      if (boardOp.checkfiveWinBreak(player) == true)
	winner = player;
    }
  else
    {
      if (boardOp.checkfiveWinNoBreak(player) == true)
	winner = player;
    }
  lastMove = pos;
  player = (player == Team::WHITE) ? Team::BLACK : Team::WHITE;
  ++nbrPlay;
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

Core::BoardOperator *Core::Referee::getBoOp()
{
  return (&boardOp);
}

Team Core::Referee::getPlayer() const
{
  return (player);
}

boardPos_t Core::Referee::getLastMove() const
{
  return (lastMove);
}

Core::IReferee *Core::Referee::clone() {
  return new Referee(*this);
}

uint16_t Core::Referee::getNbrPlay() const
{
  return (nbrPlay);
}
