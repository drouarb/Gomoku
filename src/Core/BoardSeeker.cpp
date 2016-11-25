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

void	BoardSeeker::feed(Referee *ref)
{
}

Team	BoardSeeker::simulate()
{
}

std::vector<std::pair<boardPos_t, weight_t>>	getPlayPos()
{
}

std::pair<boardPos_t, weight_t>			getBestPlay()
{
}
