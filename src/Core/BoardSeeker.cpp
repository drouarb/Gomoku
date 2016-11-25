/*
** Alexis Trouvé
*/

#include "BoardSeeker.hh"

using namespace Core;

BoardSeeker::BoardSeeker()
{
  ref = nullptr;
}

BoardSeeker::~BoardSeeker()
{
}

void	BoardSeeker::feed(Referee *nref)
{
  ref = nref;
}

Team	BoardSeeker::simulate()
{
}

std::map<boardPos_t, weight_t>	BoardSeeker::getPlayPos()
{
  std::map<boardPos_t, weight_t>		finalTab;
  std::vector<boardPos_t>			tmpTab;
  int						lenLine;
  unsigned int					i;
  Team						player;

  // recherche des lignes simple
  player = ref->getPlayer();
  lenLine = 3;
  while (lenLine < 6)
    {
      tmpTab = ref->getBoOp()->getXPossible(lenLine, player);
      i = 0;
      while (i < tmpTab.size())
	{
	  prepareTab(&finalTab, tmpTab[i], lenLine * lenLine * lenLine * lenLine);
	  ++i;
	}
      ++lenLine;
    }
  lenLine = 3;
  while (lenLine < 6)
    {
      tmpTab = ref->getBoOp()->getFreeXPossible(lenLine, player);
      i = 0;
      while (i < tmpTab.size())
	{
	  prepareTab(&finalTab, tmpTab[i], lenLine * lenLine * lenLine * lenLine);
	  ++i;
	}
      ++lenLine;
    }
  tmpTab = ref->getBoOp()->getFreeDoubleThreePos(player);
  i = 0;
  while (i < tmpTab.size())
    {
      prepareTab(&finalTab, tmpTab[i], 350);
      ++i;
    }
  tmpTab = ref->getBoOp()->getFiveBreakable(player);
  i = 0;
  while (i < tmpTab.size())
    {
      prepareTab(&finalTab, tmpTab[i], 2000);
      ++i;
    }

  /*struct {
    bool operator()(std::map<boardPos_t, weight_t>::iterator a, std::map<boardPos_t, weight_t>::iterator b)
    {
      return a->second < b->second;
    }
    } value_comparer;*/

  /*std::sort(finalTab.begin(), finalTab.end(), [](std::map<boardPos_t, weight_t>::iterator a, std::map<boardPos_t, weight_t>::iterator b)
	    {
	      return a->second < b->second;
	      });*/
  return (finalTab);
}

std::pair<boardPos_t, weight_t>			BoardSeeker::getBestPlay()
{
  std::map<boardPos_t, weight_t>		finalTab;
  std::vector<boardPos_t>			tmpTab;
  int						lenLine;
  unsigned int					i;
  Team						player;

  // recherche des lignes simple
  player = ref->getPlayer();
  lenLine = 3;
  while (lenLine < 6)
    {
      tmpTab = ref->getBoOp()->getXPossible(lenLine, player);
      i = 0;
      while (i < tmpTab.size())
	{
	  prepareTab(&finalTab, tmpTab[i], lenLine * lenLine * lenLine * lenLine);
	  ++i;
	}
      ++lenLine;
    }
  lenLine = 3;
  while (lenLine < 6)
    {
      tmpTab = ref->getBoOp()->getFreeXPossible(lenLine, player);
      i = 0;
      while (i < tmpTab.size())
	{
	  prepareTab(&finalTab, tmpTab[i], lenLine * lenLine * lenLine * lenLine);
	  ++i;
	}
      ++lenLine;
    }
  tmpTab = ref->getBoOp()->getFreeDoubleThreePos(player);
  i = 0;
  while (i < tmpTab.size())
    {
      prepareTab(&finalTab, tmpTab[i], 350);
      ++i;
    }
  tmpTab = ref->getBoOp()->getFiveBreakable(player);
  i = 0;
  while (i < tmpTab.size())
    {
      prepareTab(&finalTab, tmpTab[i], 2000);
      ++i;
    }

  /*struct {
    bool operator()(std::map<boardPos_t, weight_t>::iterator a, std::map<boardPos_t, weight_t>::iterator b)
    {
    return a->second < b->second;
    }
  } value_comparer;*/

  /*std::sort(finalTab.begin(), finalTab.end(), [](std::map<boardPos_t, weight_t>::iterator a, std::map<boardPos_t, weight_t>::iterator b)
	    {
	      return a->second < b->second;
	      });*/
  return (std::pair<boardPos_t, weight_t>(finalTab.begin()->first, finalTab.begin()->second));
}

void		BoardSeeker::prepareTab(std::map<boardPos_t, weight_t> *Tab, boardPos_t pos, weight_t weight)
{
  if (Tab->find(pos) == Tab->end())
    Tab->insert(std::pair<boardPos_t, weight_t>(pos, weight));
  else
    Tab->find(pos)->second += weight;
}
