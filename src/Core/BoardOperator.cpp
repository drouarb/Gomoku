#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator()
{
}

Core::BoardOperator::~BoardOperator()
{
}

void		Core::BoardOperator::feed(GameBoard_t *nboard)
{
  board = nboard;
}

bool		Core::BoardOperator::checkFreeDoubleThree(Team player, uint8_t x, uint8_t y)
{
  PLIST<PatternRef>		*patterns;
  PLIST<PatternRef>::iterator	it;
  Pattern			*pat;
  unsigned int			nbr3P;
  
  patterns = &patternM->getMap()[y * XBOARD + x];
  nbr3P = 0;
  it = patterns->begin();
  while (it != patterns->end())
    {
      pat = it->pattern;
      if (pat->lineLength - 2 - pat->interrupted == 3
	  && pat->line[0] && pat->line[pat->lineLength - 1]
	  && pat->line[1] == player)
	nbr3P++;
      it++;
    }
  if (nbr3P >= 2)
    return (true);
  return (false);
}

std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getFreeDoubleThreePos(Team player)
{
}

bool              Core::BoardOperator::checkEatPlayer(Team player, uint8_t x, uint8_t y)
{
  PLIST<PatternRef>	*patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

  patterns = &patternM->getMap()[y * XBOARD + x];
  it = patterns->begin();
  while (it != patterns->end())
    {
      pat = it->pattern;
      if (((pat->lineLength - 2) == 2 && pat->line[1] != player)
	  && ((pat->line[0] == player && pat->line[pat->lineLength - 1] == Team::NOPLAYER
	       && pat->posOfFirst + 3 * pat->direction == y * XBOARD + x)
	      || (pat->line[pat->lineLength - 1] == player && pat->line[0] == Team::NOPLAYER
		  && pat->posOfFirst == y * XBOARD + x)))
	return (true);
      it++;
    }
  return (false);
}

std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> Core::BoardOperator::getEatPos(Team player)
{
}

bool              Core::BoardOperator::checkfiveWin(Team player)
{
  PLIST<Pattern>	*patterns;
  PLIST<Pattern>::iterator	it;
  int				i;
  PLIST<PatternRef>	*patternsSecond;
  PLIST<PatternRef>::iterator	itSecond;
  Pattern			*patSecond;

  patterns = &patternM->getPatterns();
  it = patterns->begin();
  while (it != patterns->end())
    {
      if (it->lineLength - 2 == 5 && it->line[1] == player)
	{
	  i = 1;
	  while (i < 6)
	    {
	      patternsSecond = &patternM->getMap()[it->posOfFirst + it->direction * (i - 1)];
	      itSecond = patternsSecond->begin();
	      while (itSecond != patternsSecond->end())
		{
		  patSecond = itSecond->pattern;
		  if (patSecond->lineLength - 2 == 2)
		    if ((checkEatPlayer(player, patSecond->posOfFirst % XBOARD,
				       patSecond->posOfFirst / XBOARD) == true)
		      || checkEatPlayer(player, (patSecond->posOfFirst + 3 * patSecond->direction) % XBOARD,
					(patSecond->posOfFirst + 3 * patSecond->direction) / XBOARD) == true)
		      return (false);
		  itSecond++;
		}
	      ++i;
	    }
	  return (true);
	}
      it++;
    }
  return (false);
}


std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getXPossible(uint8_t numberPiece, Team player)
{
}

bool              Core::BoardOperator::checkBreakable(Team player)
{
  return (false);
}

Team		Core::BoardOperator::checkPos(uint8_t x, uint8_t y)
{
  return ((Team)(*board[y * XBOARD + x]));
}

uint8_t			Core::BoardOperator::applyEat(Team player, uint8_t x, uint8_t y)
{
  uint8_t		nbrEat;
  PLIST<PatternRef>	*patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

  patterns = &patternM->getMap()[y * XBOARD + x];
  it = patterns->begin();
  nbrEat = 0;
  while (it != patterns->end())
    {
      pat = it->pattern;
      if (pat->lineLength - 2 == 2 && pat->line[1] != player && ((pat->line[0] == player && pat->posOfFirst == x + y * XBOARD) || (pat->line[pat->lineLength - 1] == player && pat->posOfFirst + 3 * pat->direction == x + y * XBOARD)))
	{
	  (*board)[pat->posOfFirst + pat->direction] = Team::NOPLAYER;
	  patternM->removeStone(pat->posOfFirst + pat->direction);
	  (*board)[pat->posOfFirst + pat->direction * 2] = Team::NOPLAYER;
	  patternM->removeStone(pat->posOfFirst + pat->direction * 2);
	  nbrEat++;
	}
      it++;
    }
}

void			Core::BoardOperator::ForceupdateBoard(Team player, uint8_t x, uint8_t y)
{
  (*board)[x + y * 19] = player;
  patternM->addStone(x + y * 19, player);
}
