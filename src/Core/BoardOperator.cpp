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
    auto map = patternM.getMap();
    for (auto patref : map[pos])
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

        //look on all 8 directions for an aligned free 2-stone pattern, and a blank spot on the opposite side
        //do directions two by two, starting with the mutual condition that both sides of the center must be blank
        //this condition being checked, when a 2-stone pattern is found, you only have to check the furthest extremity to know if it is a free pattern
        int i = 5;
        while (i <= 8)
        {
            boardPos_t dir = PatternManager::checkMap[i];
            if (patternM.teamAt(pos + dir) == NOPLAYER && patternM.teamAt(pos - dir) == NOPLAYER)
            {
                for (auto patref : map[pos + dir])
                {
                    if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                        patref.pattern->direction == dir &&
                        patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                    {
                        if (findAnotherDoubleThree(player, patref.pattern->posOfFirst + (boardPos_t)1 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)2 * patref.pattern->direction, pos, pos, dir))
                            return (2);
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
                        if (findAnotherDoubleThree(player, patref.pattern->posOfFirst + (boardPos_t)1 * patref.pattern->direction, patref.pattern->posOfFirst + (boardPos_t)2 * patref.pattern->direction, pos, pos, dir))
                            return (2);
                        nbFreeThree++;
                        break;
                    }
                }
            }
            i++;
        }
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
    auto map = patternM.getMap();
    for (auto patref : map[pos])
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
                    for (auto patref : map[pos + dir])
                    {
                        if (patref.pattern->lineLength == 4 && patref.pattern->getTeam() == player &&
                            patref.pattern->direction == dir &&
                            patref.pattern->line[patref.pattern->lineLength - 1] == NOPLAYER)
                        {
                            return (true);
                        }
                    }
                    for (auto patref : map[pos - dir])
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
  PLIST<PatternRef>	patterns;
  PLIST<PatternRef>::iterator it;
  Pattern			*pat;

    boardPos_t pos = patternM.getPPos(x, y);
  patterns = patternM.getMap()[pos];
  it = patterns.begin();
  while (it != patterns.end())
    {
      pat = it->pattern;
      if (((pat->lineLength - 2) == 2 && pat->line[1] != player)
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
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;
  PLIST<PatternRef>	patSecond;
  PLIST<PatternRef>::iterator itS;
  Pattern			*pat;
  int				nbrNoBreak;
  int				i;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength - 2 >= 5 && it->line[1] == player)
	{
	  i = 1;
	  nbrNoBreak = 0;
	  while (i < it->lineLength - 1)
	    {
	      patSecond = patternM.getMap()[it->posOfFirst + i * it->direction];
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
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;

  patterns = patternM.getPatterns();
  it = patterns.begin();
  while (it != patterns.end())
    {
      if (it->lineLength - 2 >= 5 && it->line[1] == player)
	{
	  return (true);
	}
      ++it;
    }
  return (false);
}

uint8_t         Core::BoardOperator::pApplyEat(Team player, boardPos_t pos)
{
    PLIST<PatternRef>	patterns; //TODO: ref instead of copy
    PLIST<PatternRef>::iterator it;
    Pattern			*pat;
    int				save;

    patterns = patternM.getMap()[pos];
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

std::vector<boardPos_t> Core::BoardOperator::getXPossible(uint8_t numberPiece, Team player)
{
  std::vector<boardPos_t> tab;
  boardPos_t		i;
  PLIST<Pattern>	patterns;
  PLIST<Pattern>::iterator	it;

  if (numberPiece == 1)
    {
      i = 0;
      while (i < BOARDSIZE)
	{
	  if (patternM.teamAt(PatternManager::getPPos(i % XBOARD, i / XBOARD)) == Team::NOPLAYER)
	    tab.push_back(i);
	  ++i;
	}
    }
  /*else if (numberPiece >= 3)
    {
      patterns = patternM.getPatterns();
      it = patterns.begin();
      while (it != patterns.end())
	{
	  if (it->lineLength - 2 == numberPiece && it->line[1] == player)
	    {
	      if (it->line[0] == Team::NOPLAYER)
		tab.push_back(it->posOfFirst);
	      if (it->line[numberPiece + 1] == Team::NOPLAYER)
		tab.push_back(it->posOfFirst + 4 * it->direction);
	    }
	  ++it;
	}
	}*/
  return (tab);
}

std::vector<boardPos_t> Core::BoardOperator::getFreeXPossible(uint8_t numberPiece, Team player)
{
  std::vector<boardPos_t> tab;

  return (tab);
}

std::vector<boardPos_t> Core::BoardOperator::getX(uint8_t numberPiece, Team player)
{
  std::vector<boardPos_t> tab;

  return (tab);
}

std::vector<boardPos_t> Core::BoardOperator::getFreeX(uint8_t numberPiece, Team player)
{
  std::vector<boardPos_t> tab;

  return (tab);
}

std::vector<std::pair<boardPos_t, uint8_t>> Core::BoardOperator::getEatPos(Team player)
{
  std::vector<std::pair<boardPos_t, uint8_t>> tab;

  return (tab);
}

std::vector<boardPos_t> Core::BoardOperator::getFreeDoubleThreePos(Team player)
{
  std::vector<boardPos_t> tab;

  return (tab);
}

std::vector<boardPos_t> Core::BoardOperator::getFiveBreakable(Team player)
{
  std::vector<boardPos_t> tab;

  return (tab);
}

uint16_t Core::BoardOperator::getPercentDensityOnPos(boardPos_t x, boardPos_t y)
{
  uint16_t	wei = 0;
  boardPos_t	pos;
  uint8_t	dir;

  if (x < 1 || x > XBOARD - 1 || y < 1 || y > XBOARD - 1)
    return (0);
  wei += (patternM.teamAt(PatternManager::getPPos(x - 1, y - 1)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x, y - 1)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x + 1, y - 1)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x - 1, y)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x + 1, y)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x - 1, y + 1)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x, y + 1)) != Team::NOPLAYER) ? 16 : 0;
  wei += (patternM.teamAt(PatternManager::getPPos(x + 1, y + 1)) != Team::NOPLAYER) ? 16 : 0;
  return (wei);
}
