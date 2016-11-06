#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator()
{
  board = NULL;
  patternM = new PatternManager();
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
  PLIST<PatternRef>		patterns;
  PLIST<PatternRef>::iterator	it;
  PMAP<boardPos_t, PLIST<PatternRef> > Map;
  Pattern			*pat;
  unsigned int			nbr3P;
  
  Map = patternM->getMap();
  std::cout << "1" << std::endl;
  patterns = patternM->getMap()[y * XBOARD + x];
  std::cout << "2" << std::endl;
  nbr3P = 0;
  std::cout << "3" << std::endl;
  it = patterns.begin();
  std::cout << "4" << std::endl;
  while (it != patterns.end())
    {
      std::cout << "5" << std::endl;
      pat = it->pattern;
      std::cout << "6" << std::endl;
      if (pat->lineLength - 2 - pat->interrupted == 3
	  && pat->line[0] && pat->line[pat->lineLength - 1]
	  && pat->line[1] == player)
	nbr3P++;
      std::cout << "7" << std::endl;
      it++;
    }
  std::cout << "8" << std::endl;
  if (nbr3P >= 2)
    return (true);
  return (false);
}

std::vector<std::pair<uint8_t, uint8_t>> Core::BoardOperator::getFreeDoubleThreePos(Team player)
{
}

bool              Core::BoardOperator::checkEatPlayer(Team player, uint8_t x, uint8_t y)
{
  PLIST<PatternRef>	patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

  patterns = patternM->getMap()[y * XBOARD + x];
  it = patterns.begin();
  while (it != patterns.end())
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

bool              Core::BoardOperator::checkfiveWinBreak(Team player)
{
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;
  PLIST<PatternRef>	patSecond;
  PLIST<PatternRef>::iterator itS;
  Pattern			*pat;
  int				nbrNoBreak;
  int				i;

  patterns = patternM->getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength - 2 >= 5 && it->line[1] == player && it->interrupted == 0)
	{
	  i = 1;
	  nbrNoBreak = 0;
	  while (i < it->lineLength - 1)
	    {
	      patSecond = patternM->getMap()[it->posOfFirst + i * it->direction];
	      itS = patSecond.begin();
	      while (itS != patSecond.end())
		{
		    pat = itS->pattern;
		    if (pat->lineLength - 2 == 2 && pat->line[1] == player
			&& ((pat->line[0] != player && pat->line[0] != NOPLAYER
			     && pat->line[pat->lineLength - 1] == NOPLAYER)
			    || (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] != player
				&& pat->line[pat->lineLength - 1] != NOPLAYER)))
			nbrNoBreak = -1;
		  itS++;
		}
	      nbrNoBreak++;
	      if (nbrNoBreak == 5)
		return (true);
	      ++i;
	    }
	}
      it++;
    }
  return (false);
}


bool              Core::BoardOperator::checkfiveWinNoBreak(Team player)
{
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;

  patterns = patternM->getPatterns();
  it = patterns.begin();
  std::cout << "ko" << std::endl;
  while (it != patterns.end())
    {
      std::cout << "pat : " << int(it->lineLength) << std::endl;
      if (it->lineLength - 2 >= 5 && it->line[1] == player && it->interrupted == 0)
	{
	  std::cout << "true" << std::endl;
	  return (true);
	}
      it++;
    }
  std::cout << "false" << std::endl;
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
  std::cout << (Team)(*board)[y * XBOARD + x] << std::endl;
  return ((Team)(*board)[y * XBOARD + x]);
}

uint8_t			Core::BoardOperator::applyEat(Team player, uint8_t x, uint8_t y)
{
  PLIST<PatternRef>	patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

  patterns = patternM->getMap()[y * XBOARD + x];
  it = patterns.begin();
  std::cout << "a" << std::endl;
  while (it != patterns.end())
    {
      pat = it->pattern;
      if (pat->lineLength - 2 == 2 && pat->line[1] != player)
	{
	  std::cout << "pat2 ok" << std::endl;
	  std::cout << "line:[" << pat->line[0] << pat->line[1] << pat->line[2] << pat->line[3] << "]" << std::endl;
	  std::cout << "posFirst:" << pat->posOfFirst << " ,last:" << pat->posOfFirst + 3 * pat->direction << " , me:" << x + y *XBOARD << std::endl;
	  if ((pat->line[0] == player && pat->posOfFirst + 3 * pat->direction == x + y * XBOARD)
	      || (pat->line[0] == player && pat->posOfFirst == x + y * XBOARD)
	      || (pat->line[pat->lineLength - 1] == player
		  && pat->posOfFirst + 3 * pat->direction == x + y * XBOARD)
	      || (pat->line[pat->lineLength - 1] == player && pat->posOfFirst == x + y * XBOARD))
	    {
	      (*board)[pat->posOfFirst + pat->direction] = Team::NOPLAYER;
	      patternM->removeStone(pat->posOfFirst + pat->direction);
	      (*board)[pat->posOfFirst + pat->direction * 2] = Team::NOPLAYER;
	      patternM->removeStone(pat->posOfFirst + pat->direction * 2);
	      return (1 + applyEat(player, x, y));
	    }
	}
      it++;
    }
  return (0);
}

void			Core::BoardOperator::ForceupdateBoard(Team player, uint8_t x, uint8_t y)
{
  (*board)[x + y * 19] = player;
  patternM->addStone(x + y * 19, player);
}
