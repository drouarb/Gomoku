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
      board[i] = NOPLAYER; //0 ? Zero ?? ZERO ?!? COMME LE NOMBRE ?!?! PAS LA MACCRO !?!?!
      ++i;
    }
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
  boardOp->applyEat(player, x, y);
  if (boardOp->checkfiveWin(player) == true)
    winner = player;
  boardOp->ForceupdateBoard(player, x, y);
  return (true);
}

bool		Core::Referee::tryPlay(uint8_t x, uint8_t y, GameBoard_t *nboard)
{
  boardOp->feed(nboard);
  if (winner != NOPLAYER)
    return (false);
  if (boardOp->checkPos(x, y) != NOPLAYER)
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

Team	Core::Referee::getWinner() const
{
  return (winner);
}
