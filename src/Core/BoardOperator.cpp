#include "BoardOperator.hh"

Core::BoardOperator::BoardOperator() : patternM()
{ }

Core::BoardOperator::BoardOperator(const BoardOperator & other) : patternM(other.patternM), lastTakenStones(other.lastTakenStones)
{ }

Core::BoardOperator::~BoardOperator()
{ }

Core::BoardOperator & Core::BoardOperator::operator=(const BoardOperator & other)
{
    patternM = other.patternM;
    lastTakenStones = other.lastTakenStones;
}

void Core::BoardOperator::clearLastMove()
{
    lastTakenStones.clear();
}

const Core::BoardOperator::stoneList & Core::BoardOperator::getLastTakenStones() const
{
    return (lastTakenStones);
}

Team Core::BoardOperator::boardAt(boardPos_t pos)
{
  return (patternM.teamAt(pos));
}

bool		Core::BoardOperator::checkFreeDoubleThree(Team player, boardPos_t pos)
{
    patternM.addStone(pos, player);
    int foundDoubleThrees = findDoubleThree(player, pos);
    patternM.removeStone(pos);
    return (foundDoubleThrees >= 2);
}

int Core::BoardOperator::findDoubleThree(Team player, boardPos_t pos)
{
    int nbFreeThree = 0;
    for (auto patref : patternM.patternsAt(pos))
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
            /*const MAP_ENTRY * list2 = patternM.patternsAt(pos + dir);
            if (list2)*/
            for (auto patref : patternM.patternsAt(pos + dir))
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
            /*list2 = patternM.patternsAt(pos - dir);
            if (list2)*/
            for (auto patref : patternM.patternsAt(pos - dir))
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
/*
    const MAP_ENTRY * list = patternM.patternsAt(pos);
    if (list == NULL)
        return (false);
*/
    for (auto patref : patternM.patternsAt(pos))
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
                /*const MAP_ENTRY * list2 = patternM.patternsAt(pos + dir);
                if (list2)*/
                for (auto patref : patternM.patternsAt(pos + dir))
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                    {
                        return (true);
                    }
                }
                /*list2 = patternM.patternsAt(pos - dir);
                if (list2)*/
                for (auto patref : patternM.patternsAt(pos - dir))
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
        i++;
    }

    return (false);
}

bool Core::BoardOperator::isFreeAndMine(Pattern *pat, Team me)
{
    return (pat->getTeam() == me &&
            (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] == NOPLAYER));
}

bool              Core::BoardOperator::checkEatPlayer(Team player, boardPos_t pos)
{
  MAP_ENTRY::const_iterator it;
  Pattern			*pat;

  it = patternM.patternsAt(pos).begin();
  while (it != patternM.patternsAt(pos).end())
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
  PLIST::const_iterator	it;
  const MAP_ENTRY	* patSecond;
  MAP_ENTRY::const_iterator itS;
  Pattern			*pat;
  int				nbrNoBreak;
  int				i;

  PLIST & patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
  {
      if (it->lineLength >= 5 + 2 && it->line[1] == player)
      {
          i = 1;
          nbrNoBreak = 0;
          while (i < it->lineLength - 1)
          {
              /*try
              {
                  patSecond = &patternM.getMap().at(it->posOfFirst + i * it->direction);
              }
              catch (std::out_of_range)
              {
                  patSecond = NULL;
              }*/
              //if (patSecond)
              itS = patternM.patternsAt(it->posOfFirst + i * it->direction).begin();
              while (itS != patternM.patternsAt(it->posOfFirst + i * it->direction).end())
              {
                  pat = itS->pattern;
                  if (pat->lineLength == 2 + 2 && pat->line[1] == player
                      && ((pat->line[0] == OPPTEAM(player) && pat->line[pat->lineLength - 1] == NOPLAYER)
                          || (pat->line[0] == NOPLAYER && pat->line[pat->lineLength - 1] == OPPTEAM(player))))
                      nbrNoBreak = -1;
                  ++itS;
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
  PLIST	patterns;
  PLIST::const_iterator	it;

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
    MAP_ENTRY::const_iterator it;
    Pattern			*pat;
    int				save;

    if (patternM[pos].empty())
        return (0);
    it = patternM.patternsAt(pos).begin();
    //std::cout << "applyEat" << std::endl;
    while (it != patternM.patternsAt(pos).end())
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
                lastTakenStones.push_front(pat->posOfFirst + pat->direction);
                patternM.removeStone(pat->posOfFirst + pat->direction);
                //(*board)[save] = Team::NOPLAYER;
                patternM.removeStone(save);
                lastTakenStones.push_front(save);
                return (1 + pApplyEat(player, pos));
            }
        }
        ++it;
    }
    return (0);
}

uint8_t			Core::BoardOperator::applyEat(Team player, boardPos_t pos)
{
    return (pApplyEat(player, pos));
}

void			Core::BoardOperator::ForceupdateBoard(Team player, boardPos_t pos)
{
    if (player == NOPLAYER)
        patternM.removeStone(pos);
    else
        patternM.addStone(pos, player);
}

void Core::BoardOperator::getXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w)
{
  PLIST		patterns;
  PLIST::const_iterator	it;
  boardPos_t			i;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  if (numberPiece == 1)
    {
      i = XPBOARD + 1;
      while (i < PBOARDSIZE - XPBOARD - 1)
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
		      i = it->posOfFirst + (y * XPBOARD) + (x);
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
  PLIST		patterns;
  PLIST::const_iterator	it;
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
		      i = it->posOfFirst + (y * XPBOARD) + (x);
		      if (i != it->posOfFirst && patternM.teamAt(i) == Team::NOPLAYER
			  && patternM.teamAt(it->posOfFirst + yo * XPBOARD + xo) == Team::NOPLAYER)
			{
			  if (patternM.teamAt(it->posOfFirst * 2 * y * XPBOARD + 2 * x) == Team::NOPLAYER)
			    (*tab)[i] += w;
			  else if (patternM.teamAt(it->posOfFirst * 2 * y * XPBOARD + 2 * x) == player)
			    (*tab)[i] += 2 * w;
			}
		      //(*tab)[i] += w;
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
	  if (it->lineLength - 1 == numberPiece && it->line[1] == player
	      && it->line[0] == Team::NOPLAYER && it->line[it->lineLength - 1] == Team::NOPLAYER)
	    {
	      if (patternM.teamAt(it->posOfFirst - it->direction) == Team::NOPLAYER)
		(*tab)[it->posOfFirst] += w;
	      else if (patternM.teamAt(it->posOfFirst - it->direction) == player)
		(*tab)[it->posOfFirst] += w * 2;
	      if (patternM.teamAt(it->posOfFirst + (numberPiece + 2) * it->direction) == Team::NOPLAYER)
		(*tab)[it->posOfFirst + (numberPiece + 1) * it->direction] += w;
	      else if (patternM.teamAt(it->posOfFirst + (numberPiece + 2) * it->direction) == player)
		(*tab)[it->posOfFirst + (numberPiece + 1) * it->direction] += w * 2;
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
  PLIST		patterns;
  PLIST::const_iterator	it;

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
  PLIST		patterns;
  PLIST::const_iterator	it;
  const MAP_ENTRY	*patSecond;
  MAP_ENTRY::const_iterator itS;
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
	      //patSecond = patternM.patternsAt(it->posOfFirst + i * it->direction);
	      //patSecond = patternM.getMap()[it->posOfFirst + i * it->direction];
	      itS = patternM.patternsAt(it->posOfFirst + i * it->direction).begin();
	      while (itS != patternM.patternsAt(it->posOfFirst + i * it->direction).end())
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
  int i;

  repX = x;
  i = y * XPBOARD + x;
  y -= DENSITYRANGE;
  while (range <= DENSITYRANGE)
    {
      x = repX - range;
      while (x <= repX + range)
	{
	  if ((y * XPBOARD + x) > 0 && (y * XPBOARD + x) < PBOARDSIZE - 1 &&
	      patternM.teamAt(y * XPBOARD + x) > Team::NOPLAYER)
	    {
	      (*tab)[y * XPBOARD + x] += w;
	    }
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
	  if ((y * XPBOARD + x) > 0 && (y * XPBOARD + x) < PBOARDSIZE - 1 &&
	      patternM.teamAt(y * XPBOARD + x) > Team::NOPLAYER)
	    {
	      (*tab)[y * XPBOARD + x] += w;
	    }
	  ++x;
	}
      ++y;
      --range;
    }
}

const Core::PatternManager &Core::BoardOperator::getPatternManager() const
{
    return (patternM);
}

Core::PatternManager &Core::BoardOperator::getPatternManager()
{
    return (patternM);
}
