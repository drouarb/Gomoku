#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator()
{ }

Core::BoardOperator::BoardOperator(const BoardOperator & other) : patternM(other.patternM)
{ }

Core::BoardOperator::~BoardOperator()
{ }

Team Core::BoardOperator::boardAt(boardPos_t x, boardPos_t y)
{
    return (patternM.teamAt(PatternManager::getPPos(x, y)));
}

bool		Core::BoardOperator::checkFreeDoubleThree(Team player, boardPos_t x, boardPos_t y)
{
    boardPos_t pos = patternM.getPPos(x, y);
    patternM.addStone(pos, player);
    int foundDoubleThrees = findDoubleThree(player, pos);
    patternM.removeStone(pos);
    return (foundDoubleThrees >= 2);
}

int Core::BoardOperator::findDoubleThree(Team player, boardPos_t pos)
{
    int nbFreeThree = 0;
    const auto & map = patternM.getMap();
    const PLIST<PatternRef> * list = patternM.patternsAt(pos);
    if (list == NULL)
        return (0);
    for (auto patref : *list)
    {
        if (patref.pattern->lineLength == 5)
        {
            if (isFreeAndMine(patref.pattern, player))
            {
                if (findAnotherDoubleThree(player, patref.pattern->posOfFirst + (boardPos_t)1 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)2 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)3 * patref.pattern->direction, pos, patref.pattern->direction))
                    return (2);
                nbFreeThree++;
            }
        }
        else if (patref.pattern->lineLength == 4)
        {
            if (isFreeAndMine(patref.pattern, player))
            {
                //look at both extremities for single stone followed by blank
                if (patternM.teamAt(patref.pattern->posOfFirst + (boardPos_t) 4 * patref.pattern->direction) == player &&
                    patternM.teamAt(patref.pattern->posOfFirst + (boardPos_t) 5 * patref.pattern->direction) == NOPLAYER)
                {
                    if (findAnotherDoubleThree(player, patref.pattern->posOfFirst + (boardPos_t)1 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)2 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t) 4 * patref.pattern->direction, pos, patref.pattern->direction))
                        return (2);
                    nbFreeThree++;
                }
                else if (patternM.teamAt(patref.pattern->posOfFirst - (boardPos_t) 1 * patref.pattern->direction) == player &&
                         patternM.teamAt(patref.pattern->posOfFirst - (boardPos_t) 2 * patref.pattern->direction) == NOPLAYER)
                {
                    if (findAnotherDoubleThree(player, patref.pattern->posOfFirst + (boardPos_t)1 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)2 * patref.pattern->direction, patref.pattern->posOfFirst - (boardPos_t) 1 * patref.pattern->direction, pos, patref.pattern->direction))
                        return (2);
                    nbFreeThree++;
                }
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
        if (patternM.teamAt(pos + dir) == NOPLAYER && patternM.teamAt(pos - dir) == NOPLAYER)
        {
            const PLIST<PatternRef> * list2 = patternM.patternsAt(pos + dir);
            if (list2)
            {
                for (auto patref : *list2)
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                    {
                        if (findAnotherDoubleThree(player, patref.pattern->posOfFirst +
                                                           (boardPos_t) 1 * patref.pattern->direction,
                                                   patref.pattern->posOfFirst +
                                                   (boardPos_t) 2 * patref.pattern->direction, pos, pos, dir))
                            return (2);
                        nbFreeThree++;
                        break;
                    }
                }
            }
            list2 = patternM.patternsAt(pos - dir);
            if (list2)
            {
                for (auto patref : *list2)
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[0] == NOPLAYER)
                    {
                        if (findAnotherDoubleThree(player, patref.pattern->posOfFirst +
                                                           (boardPos_t) 1 * patref.pattern->direction,
                                                   patref.pattern->posOfFirst +
                                                   (boardPos_t) 2 * patref.pattern->direction, pos, pos, dir))
                            return (2);
                        nbFreeThree++;
                        break;
                    }
                }
            }
        }
        i++;
    }

    return (nbFreeThree);
}

bool Core::BoardOperator::findAnotherDoubleThree(Team player, boardPos_t pos1, boardPos_t pos2, boardPos_t pos3, boardPos_t me, boardPos_t ommittedDir)
{
    if (pos1 != me && checkPosForDoubleThree(player, pos1, ommittedDir))
        return (true);
    if (pos2 != me && checkPosForDoubleThree(player, pos2, ommittedDir))
        return (true);
    if (pos3 != me && checkPosForDoubleThree(player, pos3, ommittedDir))
        return (true);
    return (false);
}

bool Core::BoardOperator::checkPosForDoubleThree(Team player, boardPos_t pos, boardPos_t ommittedDir)
{
    const PLIST<PatternRef> * list = patternM.patternsAt(pos);
    if (list == NULL)
        return (false);
    for (auto patref : *list)
    {
        if (patref.pattern->lineLength == 5)
        {
            if (patref.pattern->direction != ommittedDir && isFreeAndMine(patref.pattern, player))
            {
                return (true);
            }
        }
        else if (patref.pattern->lineLength == 4)
        {
            if (patref.pattern->direction != ommittedDir && isFreeAndMine(patref.pattern, player))
            {
                //look at both extremities for single stone followed by blank
                if (patternM.teamAt(patref.pattern->posOfFirst + (boardPos_t) 4 * patref.pattern->direction) == player &&
                    patternM.teamAt(patref.pattern->posOfFirst + (boardPos_t) 5 * patref.pattern->direction) == NOPLAYER)
                {
                    return (true);
                }
                else if (patternM.teamAt(patref.pattern->posOfFirst - (boardPos_t) 1 * patref.pattern->direction) == player &&
                         patternM.teamAt(patref.pattern->posOfFirst - (boardPos_t) 2 * patref.pattern->direction) == NOPLAYER)
                {
                    return (true);
                }
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
        if (dir != ommittedDir)
        {
            if (patternM.teamAt(pos + dir) == NOPLAYER && patternM.teamAt(pos - dir) == NOPLAYER)
            {
                const PLIST<PatternRef> * list2 = patternM.patternsAt(pos + dir);
                if (list2)
                {
                    for (auto patref : *list2)
                    {
                        if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                            patref.pattern->direction == dir &&
                            patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                        {
                            return (true);
                        }
                    }
                }
                list2 = patternM.patternsAt(pos - dir);
                if (list2)
                {
                    for (auto patref : *list2)
                    {
                        if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                            patref.pattern->direction == dir &&
                            patref.pattern->line[0] == NOPLAYER)
                        {
                            return (true);
                        }
                    }
                }
            }
        }
        i++;
    }

    return (false);
}

bool Core::BoardOperator::isFreeAndMine(Pattern *pat, Team me)
{
    return (pat->getTeam() == me &&
            (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] == NOPLAYER));
}

bool              Core::BoardOperator::checkEatPlayer(Team player, boardPos_t x, boardPos_t y)
{
  const PLIST<PatternRef>	* patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

    boardPos_t pos = patternM.getPPos(x, y);
    try
    {
        patterns = &patternM.getMap().at(pos);
    }
    catch (std::out_of_range)
    {
        return (false);
    }
  it = patterns->begin();
  while (it != patterns->end())
    {
      pat = it->pattern;
      if (((pat->lineLength) == 2 + 2 && pat->line[1] != player)
	  && ((pat->line[0] == player && pat->line[pat->lineLength - 1] == Team::NOPLAYER
	       && pat->posOfFirst + 3 * pat->direction == pos)
	      || (pat->line[pat->lineLength - 1] == player && pat->line[0] == Team::NOPLAYER
		  && pat->posOfFirst == pos)))
	return (true);
      ++it;
    }
  return (false);
}

bool              Core::BoardOperator::checkfiveWinBreak(Team player)
{
  PLIST<Pattern>::iterator	it;
  const PLIST<PatternRef>	* patSecond;
  PLIST<PatternRef>::iterator itS;
  Pattern			*pat;
  int				nbrNoBreak;
  int				i;

  PLIST<Pattern> & patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
  {
      if (it->lineLength >= 5 + 2 && it->line[1] == player)
      {
          i = 1;
          nbrNoBreak = 0;
          while (i < it->lineLength - 1)
          {
              try
              {
		patSecond = &patternM.getMap().at(it->posOfFirst + i * it->direction);
              }
              catch (std::out_of_range)
              {
                  patSecond = NULL;
              }
              if (patSecond)
              {
                  itS = patSecond->begin();
                  while (itS != patSecond->end())
                  {
                      pat = itS->pattern;
                      if (pat->lineLength == 2 + 2 && pat->line[1] == player
                          && ((pat->line[0] != player && pat->line[0] != NOPLAYER
                               && pat->line[pat->lineLength - 1] == NOPLAYER)
                              || (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] != player
                                  && pat->line[pat->lineLength - 1] != NOPLAYER)))
                          nbrNoBreak = -1;
                      ++itS;
                  }
              }
              nbrNoBreak++;
              if (nbrNoBreak == 5)
                  return (true);
              ++i;
          }
      }
      ++it;
  }
  return (false);
}


bool              Core::BoardOperator::checkfiveWinNoBreak(Team player)
{
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength >= 5 + 2 && it->line[1] == player)
	{
	  return (true);
	}
      ++it;
    }
  return (false);
}

uint8_t         Core::BoardOperator::pApplyEat(Team player, boardPos_t pos)
{
    const PLIST<PatternRef> * patterns;
    PLIST<PatternRef>::iterator it;
    Pattern			*pat;
    int				save;

    try
    {
        patterns = &patternM.getMap().at(pos);
    }
    catch (std::out_of_range)
    {
        return (0);
    }
    it = patterns->begin();
    //std::cout << "applyEat" << std::endl;
    while (it != patterns->end())
    {
        pat = it->pattern;
        if (pat->lineLength == 2 + 2 && pat->line[1] != player)
        {
            //std::cout << "applyEat : pat2 find" << std::endl;
            //std::cout << "line:[" << pat->line[0] << pat->line[1] << pat->line[2] << pat->line[3] << "]" << std::endl;
            //std::cout << "posFirst:" << pat->posOfFirst << " ,last:" << pat->posOfFirst + 3 * pat->direction << " , me:" << x + y *XBOARD << std::endl;
            if ((pat->line[0] == player && pat->posOfFirst + 3 * pat->direction == pos)
                || (pat->line[0] == player && pat->posOfFirst == pos)
                || (pat->line[pat->lineLength - 1] == player
                    && pat->posOfFirst + 3 * pat->direction == pos)
                || (pat->line[pat->lineLength - 1] == player && pat->posOfFirst == pos))
            {
                save = pat->posOfFirst + pat->direction * 2;
                //(*board)[pat->posOfFirst + pat->direction] = Team::NOPLAYER;
                patternM.removeStone(pat->posOfFirst + pat->direction);
                //(*board)[save] = Team::NOPLAYER;
                patternM.removeStone(save);
                return (1 + pApplyEat(player, pos));
            }
        }
        ++it;
    }
    return (0);
}

uint8_t			Core::BoardOperator::applyEat(Team player, boardPos_t x, boardPos_t y)
{
    return (pApplyEat(player, patternM.getPPos(x, y)));
}

void			Core::BoardOperator::ForceupdateBoard(Team player, boardPos_t x, boardPos_t y)
{
  patternM.addStone(patternM.getPPos(x, y), player);
}

void Core::BoardOperator::getXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w)
{
  PLIST<Pattern>		patterns;
  PLIST<Pattern>::iterator	it;
  boardPos_t			i;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  if (numberPiece == 1)
    {
      i = 0;
      while (i < BOARDSIZE)
	{
	  if (patternM.teamAt(i) == Team::NOPLAYER)
	    (*tab)[i] += w;
	  ++i;
	}
    }
  else if (numberPiece == 2)
    {
      while (it != patterns.end())
	{
	  if (it->lineLength == 1 && it->line[0] == player)
	    {
	      int x;
	      int y = -1;
	      while (y < 2)
		{
		  x = -1;
		  while (x < 2)
		    {
		      i = it->posOfFirst + (y * XBOARD) + (x);
		      if (i != it->posOfFirst && patternM.teamAt(i) == Team::NOPLAYER)
			(*tab)[i] += w;
		      ++x;
		    }
		  ++y;
		}
	    }
	  ++it;
	}
    }
  else
    {
      while (it != patterns.end())
	{
	  if (it->lineLength - 2 == numberPiece && it->line[1] == player)
	    {
	      if (it->line[0] == Team::NOPLAYER)
		(*tab)[it->posOfFirst] += w;
	      if (it->line[it->lineLength - 1] == Team::NOPLAYER)
		(*tab)[it->posOfFirst + (numberPiece + 1) * it->direction] += w;
	    }
	  ++it;
	}
    }
}

void Core::BoardOperator::getFreeXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w)
{
  PLIST<Pattern>		patterns;
  PLIST<Pattern>::iterator	it;
  boardPos_t			i;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  if (numberPiece == 2)
    {
      while (it != patterns.end())
	{
	  if (it->lineLength == 1 && it->line[0] == player)
	    {
	      int x;
	      int y = -1;
	      int xo;
	      int yo = 1;
	      while (y < 2)
		{
		  x = -1;
		  xo = 1;
		  while (x < 2)
		    {
		      i = it->posOfFirst + (y * XBOARD) + (x);
		      if (i != it->posOfFirst && patternM.teamAt(i) == Team::NOPLAYER
			  && patternM.teamAt(it->posOfFirst + yo * XBOARD + xo) == Team::NOPLAYER)
			{
			  if (patternM.teamAt(it->posOfFirst * 2 * y * XBOARD + 2 * x) == Team::NOPLAYER)
			    (*tab)[i] += w;
			  else if (patternM.teamAt(it->posOfFirst * 2 * y * XBOARD + 2 * x) == player)
			    (*tab)[i] += 2 * w;
			}
			(*tab)[i] += w;
		      --xo;
		      ++x;
		    }
		  --yo;
		  ++y;
		}
	    }
	  ++it;
	}
    }
  else if (numberPiece >= 3)
    {
      while (it != patterns.end())
	{
	  if (it->lineLength - 2 == numberPiece && it->line[1] == player
	      && it->line[0] > Team::NOPLAYER && it->line[it->lineLength - 1] > Team::NOPLAYER)
	    {
	      if (patternM.teamAt(it->posOfFirst - it->direction) == Team::NOPLAYER)
		(*tab)[it->posOfFirst] += w;
	      else if (patternM.teamAt(it->posOfFirst - it->direction) == player)
		(*tab)[it->posOfFirst] += w * 2;
	      if (patternM.teamAt(it->posOfFirst + (numberPiece + 2) * it->direction) == Team::NOPLAYER)
		(*tab)[it->posOfFirst] += w;
	      else if (patternM.teamAt(it->posOfFirst + (numberPiece + 2) * it->direction) == player)
		(*tab)[it->posOfFirst] += w * 2;
	    }
	  ++it;
	}
    }
}

void Core::BoardOperator::getX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w)
{
}

void Core::BoardOperator::getFreeX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w)
{
}

void Core::BoardOperator::getEatPos(Team player, std::vector<boardPos_t> *tab, weight_t w)
{
  PLIST<Pattern>		patterns;
  PLIST<Pattern>::iterator	it;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength - 2 == 2 && it->line[1] == !player)
	{
	  if (it->line[0] == player && it->line[3] == Team::NOPLAYER)
	    (*tab)[it->posOfFirst + 3 * it->direction] +=w;
	  else if (it->line[3] == player && it->line[0] == Team::NOPLAYER)
	    (*tab)[it->posOfFirst] += w;
	}
      ++it;
    }
}

void Core::BoardOperator::getFreeDoubleThreePos(Team player, std::vector<boardPos_t> *tab, weight_t w)
{
}

void Core::BoardOperator::getFiveBreakable(Team player, std::vector<boardPos_t> *tab, weight_t w)
{
  PLIST<Pattern>		patterns;
  PLIST<Pattern>::iterator	it;
  const PLIST<PatternRef>	*patSecond;
  PLIST<PatternRef>::iterator itS;
  Pattern			*pat;
  boardPos_t			i;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength - 2 == 5 && it->line[1] == player)
	{
	  i = 1;
	  while (i < it->lineLength - 1)
	    {
	      patSecond = &patternM.getMap().at(it->posOfFirst + i * it->direction);
	      //patSecond = patternM.getMap()[it->posOfFirst + i * it->direction];
	      itS = patSecond->begin();
	      while (itS != patSecond->end())
		{
		  pat = itS->pattern;
		  if (pat->lineLength - 2 == 2 && pat->line[1] == player
		      && pat->line[0] == Team::NOPLAYER
		      && pat->line[pat->lineLength - 1] == Team::NOPLAYER)
		    {
		      (*tab)[pat->posOfFirst] += w;
		      (*tab)[pat->posOfFirst + 3 * pat->direction] += w;
		    }
		  ++itS;
		}
	      ++i;
	    }
	}
      ++it;
    }
}

void Core::BoardOperator::getPercentDensityOnPos(boardPos_t x, boardPos_t y, std::vector<boardPos_t> *tab, weight_t w)
{
  int range = 0;
  int repX;

  repX = x;
  while (range <= DENSITYRANGE)
    {
      x = repX - range;
      while (x <= repX + range)
	{
	  if (patternM.teamAt(y * XBOARD + x) > Team::NOPLAYER)
	    (*tab)[y * XBOARD + x] += w;
	  ++x;
	}
      ++y;
      ++range;
    }
  --range;
  while (range >= 0)
    {
      x = repX - range;
      while (x <= repX + range)
	{
	  if (patternM.teamAt(y * XBOARD + x) > Team::NOPLAYER)
	    (*tab)[y * XBOARD + x] += w;
	  ++x;
	}
      ++y;
      --range;
    }
}
