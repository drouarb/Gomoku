#include "Referee.hpp"
#include "PatternManager.hh"
#include <string.h>
#include <Core/BoardEvaluator.hh>

Core::Referee::Referee() : gameId(0)
{
  initialize();
}


Core::Referee::Referee(const Referee & other) :
        boardOp(other.boardOp), stats(other.stats),
        player(other.player), winner(other.winner), rRules(other.rRules),
	lastMove(other.lastMove), nbrPlay(other.nbrPlay), gameId(other.gameId)
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
    gameId++;
}

GameBoard_t	Core::Referee::getBoardCopy()
{
  GameBoard_t	newBoard;


    std::cout << "--------------- " << std::to_string(player) << std::endl;
    auto vect = BoardEvaluator::getInstance()->getInterestingMoves(this);
    for (auto it : *vect)
    {
        std::cout << "y=" << std::to_string(it.first / XPBOARD) << " x=" << std::to_string(it.first % XPBOARD) << " i=" << std::to_string(it.first) << " weight=" << std::to_string(-it.second) << std::endl;
    }
    std::cout << boardOp.getPatternManager() << std::endl;


    newBoard = new Team[BOARDSIZE];
    for (int y = 0; y < XBOARD; y++)
    {
        for (int x = 0; x < XBOARD; x++)
        {
            newBoard[y * XBOARD + x] = boardOp.boardAt(PatternManager::getPPos(x, y));
        }
    }
  return (newBoard);
}

void		Core::Referee::setPlayer(Team nplayer)
{
    player = nplayer;
}

bool        Core::Referee::tryPlay(boardPos_t x, boardPos_t y)
{
    return (tryPlay(PatternManager::getPPos(x, y)));
}

bool		Core::Referee::tryPlay(boardPos_t pos)
{
    boardOp.clearLastMove();
  if (winner != NOPLAYER)
    return (false);
  if (boardOp.boardAt(pos) != NOPLAYER)
    return (false);
  if ((*rRules)[DOUBLE_THREE].on == true)
    if (boardOp.checkFreeDoubleThree(player, pos) == true)
      return (false);
  stats[player].eaten += boardOp.applyEat(player, pos);
  boardOp.ForceupdateBoard(player, pos);
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

void Core::Referee::undoLastMove()
{
    player = (player == Team::WHITE) ? Team::BLACK : Team::WHITE;
    winner = NOPLAYER;
    stats[player].eaten -= boardOp.getLastTakenStones().size() / 2;
    for (auto pos : boardOp.getLastTakenStones())
    {
        boardOp.ForceupdateBoard(OPPTEAM(getPlayer()), pos);
    }
    boardOp.clearLastMove();
    boardOp.ForceupdateBoard(NOPLAYER, lastMove);
}

uint16_t Core::Referee::getNbrPlay() const
{
  return (nbrPlay);
}

char Core::Referee::getGameId() const {
    return gameId;
}
