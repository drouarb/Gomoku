/*
** Alexis Trouvé
*/

#ifndef BOARDSEEKER
#define BOARDSEEKER

#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include "Definitions.hh"
#include "Referee.hpp"
#include "BoardOperator.hh"
#include "Helpers/fastList.hpp"

typedef uint16_t weight_t;

namespace Core
{
  class BoardSeeker
  {
  public:
    BoardSeeker();
    ~BoardSeeker();
    static fastList<boardPos_t>		*getPlayPos(IReferee *ref);
    static boardPos_t			getBestPlay(IReferee *ref);
    static void	prepareTab(std::map<boardPos_t, weight_t> *Tab, boardPos_t pos, weight_t weight);
  };
}

#endif
