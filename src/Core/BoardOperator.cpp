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

bool		Core::BoardOperator::checkThreeFreeOnMe(Team player, Pattern *patS)
{
  PLIST<PatternRef>		patterns;
  PLIST<PatternRef>::iterator	it;
  Pattern			*pat;
  int				i;

  i = 1;
  ////std::cout << "lookSecondThree" << std::endl;
  while (i < patS->lineLength - 2)
    {
      patterns = patternM->getMap()[patS->posOfFirst + i * patS->direction];
      it = patterns.begin();
      ////std::cout << "check for pos :" << i << std::endl;
      while (it != patterns.end())
	{
	  pat = it->pattern;
	  ////std::cout << "pattern: len:" << int(pat->lineLength - 2) << " ,pos:" << pat->posOfFirst << " ,dir:" << pat->direction << std::endl;
	  if (pat != patS && pat->lineLength - 2 >= 3 && pat->line[0] == NOPLAYER //TODO: optimize (e.g. replace -2 >= 3 by >= 5)
	      && pat->line[pat->lineLength - 1] == NOPLAYER
	      && pat->line[1] == player)
	    {
	      return (true);
	    }
	  it++;
	}
      ++i;
    }
  return (false);
}

bool		Core::BoardOperator::checkFreeDoubleThree(Team player, uint8_t x, uint8_t y)
{
    boardPos_t pos = (boardPos_t)(y * XBOARD + x);
    patternM->addStone(pos, player);
    int nbFreeThree = 0;
    auto map = patternM->getMap();
    for (auto patref : map[pos])
    {
        //TODO: replace ifs by fun ptr tab with lineLength as index, returning number of free 3s found
        if (patref.pattern->lineLength == 5)
        {
            if (isFreeAndMine(patref.pattern, player))
            {
                nbFreeThree++;
            }
        }
        else if (patref.pattern->lineLength == 4)
        {
            if (isFreeAndMine(patref.pattern, player))
            {
                //look at both extremities for single stone followed by blank
                if (patternM->teamAt(patref.pattern->posOfFirst + (boardPos_t) 4 * patref.pattern->direction) == player &&
                    patternM->teamAt(patref.pattern->posOfFirst + (boardPos_t) 5 * patref.pattern->direction) == NOPLAYER)
                {
                    nbFreeThree++;
                }
                else if (patternM->teamAt(patref.pattern->posOfFirst - (boardPos_t) 1 * patref.pattern->direction) == player &&
                         patternM->teamAt(patref.pattern->posOfFirst - (boardPos_t) 2 * patref.pattern->direction) == NOPLAYER)
                {
                    nbFreeThree++;
                }
            }
        }

        //look on all 8 directions for an aligned free 2-stone pattern, and a blank spot on the opposite side
        //do directions two by two, starting with the mutual condition that both sides of the center must be blank
        //this condition being checked, when a 2-stone pattern is found, you only have to check the furthest extremity to know if it is a free pattern
        int i = 5;
        while (i <= 8)
        {
            boardPos_t dir = PatternManager::checkMap[i];
            if (patternM->teamAt(pos + dir) == NOPLAYER && patternM->teamAt(pos - dir) == NOPLAYER)
            {
                for (auto patref : map[pos + dir])
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                    {
                        nbFreeThree++;
                        break;
                    }
                }
                for (auto patref : map[pos - dir])
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[0] == NOPLAYER)
                    {
                        nbFreeThree++;
                        break;
                    }
                }
            }
            i++;
        }
    }
    patternM->removeStone(pos);
    return (nbFreeThree >= 2);



/*
  PLIST<PatternRef>		patterns;
  PLIST<PatternRef>::iterator	it;
  Pattern			*pat;

  ////std::cout << "checkFreeDoubleThree" << std::endl;
  patternM->addStone(x + y * XBOARD, player);
  patterns = patternM->getMap()[y * XBOARD + x];
  it = patterns.begin();
  while (it != patterns.end())
    {
      pat = it->pattern;
      if (pat->lineLength - 2 >= 3
	  && pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] == NOPLAYER
	  && pat->line[1] == player)
	{
	  ////std::cout << "pattern3 find" << std::endl;
	  ////std::cout << "line:[" << pat->line[0] << pat->line[1] << pat->line[2] << pat->line[3] << pat->line[4] << "]" << std::endl;
	  if (checkThreeFreeOnMe(player, pat) == true)
      {
          patternM->removeStone(x + y * XBOARD);
          return (true);
      }
	}
      it++;
    }
  patternM->removeStone(x + y * XBOARD);
  return (false);
*/
}

bool Core::BoardOperator::isFreeAndMine(Pattern *pat, Team me)
{
    return (pat->getTeam() == me &&
            (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] == NOPLAYER));
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
      if (it->lineLength - 2 >= 5 && it->line[1] == player)
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
  while (it != patterns.end())
    {
      if (it->lineLength - 2 >= 5 && it->line[1] == player)
	{
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
  return ((Team)(*board)[y * XBOARD + x]);
}

uint8_t			Core::BoardOperator::applyEat(Team player, uint8_t x, uint8_t y)
{
  PLIST<PatternRef>	patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;
  int				save;

  patterns = patternM->getMap()[y * XBOARD + x];
  it = patterns.begin();
  //std::cout << "applyEat" << std::endl;
  while (it != patterns.end())
    {
      pat = it->pattern;
      if (pat->lineLength - 2 == 2 && pat->line[1] != player)
	{
	  //std::cout << "applyEat : pat2 find" << std::endl;
	  //std::cout << "line:[" << pat->line[0] << pat->line[1] << pat->line[2] << pat->line[3] << "]" << std::endl;
	  //std::cout << "posFirst:" << pat->posOfFirst << " ,last:" << pat->posOfFirst + 3 * pat->direction << " , me:" << x + y *XBOARD << std::endl;
	  if ((pat->line[0] == player && pat->posOfFirst + 3 * pat->direction == x + y * XBOARD)
	      || (pat->line[0] == player && pat->posOfFirst == x + y * XBOARD)
	      || (pat->line[pat->lineLength - 1] == player
		  && pat->posOfFirst + 3 * pat->direction == x + y * XBOARD)
	      || (pat->line[pat->lineLength - 1] == player && pat->posOfFirst == x + y * XBOARD))
	    {
	      save = pat->posOfFirst + pat->direction * 2;
	      (*board)[pat->posOfFirst + pat->direction] = Team::NOPLAYER;
	      patternM->removeStone(pat->posOfFirst + pat->direction);
	      (*board)[save] = Team::NOPLAYER;
	      patternM->removeStone(save);
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
