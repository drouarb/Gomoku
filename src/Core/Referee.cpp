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
  //if (rRules[DOUBLE_THREE].on == true)
  if (boardOp->checkFreeDoubleThree(player, x, y) == true)
    return (false);
  std::cout << "d winner = " << winner << std::endl;
  stats[player].eaten += boardOp->applyEat(player, x, y);
  boardOp->ForceupdateBoard(player, x, y);
  std::cout << "eaten by " << player << " : " << int(stats[player].eaten) << std::endl;
  if (stats[player].eaten >= EATWIN)
    winner = player;
  if (rRules[BREAKABLE_FIVE].on == true)
    {
      std::cout << "with5 winner = " << winner << std::endl;
      if (boardOp->checkfiveWinBreak(player) == true)
	winner = player;
    }
  else
    {
      if (boardOp->checkfiveWinNoBreak(player) == true)
	winner = player;
    }
  std::cout << "h winner = " << winner << std::endl;
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

void		Core::Referee::feedRules(std::map<RuleID, Rule> rules)
{
  rRules = rules;
}

Team	Core::Referee::getWinner() const
{
  return (winner);
}

uint8_t	Core::Referee::getTeamEat(Team player)
{
  return (stats[player].eaten * 2);
}
