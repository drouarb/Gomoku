/*
** Alexis Trouvé
*/

#include "BoardSeeker.hh"

using namespace Core;

BoardSeeker::BoardSeeker()
{
}

BoardSeeker::~BoardSeeker()
{
}

static bool comparePair(std::pair<boardPos_t, weight_t>& pos1, std::pair<boardPos_t, weight_t>& pos2)
{
  if (pos1.second > pos2.second)
    return (true);
  return (false);
}

std::list<std::pair<boardPos_t, weight_t>>	*BoardSeeker::getPlayPos(IReferee *ref)
{
  std::vector<boardPos_t>	tab;
  unsigned int			i;
  std::list<std::pair<boardPos_t, weight_t>>	*list = new std::list<std::pair<boardPos_t, weight_t>>;

  i = XPBOARD + 1;
  tab.reserve(PBOARDSIZE);
  while (i < PBOARDSIZE)
    {
      tab.push_back(0);
      ++i;
    }
  std::cout << "getXPos friend" << std::endl;
  //ref->getBoOp()->getXPossible(2, ref->getPlayer(), &tab, 0);
  ref->getBoOp()->getXPossible(3, ref->getPlayer(), &tab, 30);
  ref->getBoOp()->getXPossible(4, ref->getPlayer(), &tab, 200);
  ref->getBoOp()->getXPossible(5, ref->getPlayer(), &tab, 1000);
  std::cout << "getXPos enemie" << std::endl;
  //ref->getBoOp()->getXPossible(2, !ref->getPlayer(), &tab, 5);
  ref->getBoOp()->getXPossible(3, !ref->getPlayer(), &tab, 25);
  ref->getBoOp()->getXPossible(4, !ref->getPlayer(), &tab, 150);
  ref->getBoOp()->getXPossible(5, !ref->getPlayer(), &tab, 950);
  std::cout << "getPosfree amis" << std::endl;
  //ref->getBoOp()->getFreeXPossible(2, ref->getPlayer(), &tab, 20);
  ref->getBoOp()->getFreeXPossible(3, ref->getPlayer(), &tab, 300);
  ref->getBoOp()->getFreeXPossible(4, ref->getPlayer(), &tab, 600);
  std::cout << "getPosfree enemis" << std::endl;
  //ref->getBoOp()->getFreeXPossible(2, !ref->getPlayer(), &tab, 10);
  ref->getBoOp()->getFreeXPossible(3, !ref->getPlayer(), &tab, 350);
  ref->getBoOp()->getFreeXPossible(4, !ref->getPlayer(), &tab, 500);
  std::cout << "checkeat pos" << std::endl;
  ref->getBoOp()->getEatPos(ref->getPlayer(), &tab, 400);// savoir combien j'ai mangé
  ref->getBoOp()->getEatPos(!ref->getPlayer(), &tab, 300);// savoir combien j'ai mangé
  std::cout << "check doublethree free" << std::endl;
  ref->getBoOp()->getFreeDoubleThreePos(ref->getPlayer(), &tab, 200);
  ref->getBoOp()->getFreeDoubleThreePos(!ref->getPlayer(), &tab, 199);
  std::cout << "check five breakable" << std::endl;
  ref->getBoOp()->getFiveBreakable(ref->getPlayer(), &tab, 1);
  ref->getBoOp()->getFiveBreakable(!ref->getPlayer(), &tab, 500);
  i = XPBOARD + 1;
  std::cout << "checkdensity" << std::endl;
  while (i < PBOARDSIZE - XPBOARD - 1)
    {
      if (i % XPBOARD > 0 && i % XPBOARD < XPBOARD - 1 && i / XPBOARD > 0 && i / XPBOARD < XPBOARD - 1)
	ref->getBoOp()->getPercentDensityOnPos(i % XPBOARD, i / XPBOARD, &tab, 1);
      ++i;
    }
  i = 0;
  std::cout << "addtolist" << std::endl;
  //list.reserve(40);
  while (i < PBOARDSIZE)
    {
      if (tab[i] > 0 && i % XPBOARD > 0 && i % XPBOARD < XPBOARD - 1 && i / XPBOARD > 0 && i / XPBOARD < XPBOARD - 1) 
	{
	  list->push_back(std::pair<boardPos_t, weight_t>(i - XPBOARD - 2 * (i / XPBOARD), tab[i]));
	  std::cout << "WEIGHT pos: " << (i - XPBOARD - 2 * (i / XPBOARD)) << " = " << tab[i] << std::endl;
	}
      ++i;
    }
  std::cout << "sort list" << std::endl;
  list->sort(comparePair);
  std::cout << "return" << std::endl;
  return (list);
}

boardPos_t					BoardSeeker::getBestPlay(IReferee *ref)
{
  /*fastList<boardPos_t> *list;

  list = BoardSeeker::getPlayPos(ref);
  return (list->begin().elem->value);*/
}

void		BoardSeeker::prepareTab(std::map<boardPos_t, weight_t> *Tab, boardPos_t pos, weight_t weight)
{
  if (Tab->find(pos) == Tab->end())
    Tab->insert(std::pair<boardPos_t, weight_t>(pos, weight));
  else
    Tab->find(pos)->second += weight;
}
