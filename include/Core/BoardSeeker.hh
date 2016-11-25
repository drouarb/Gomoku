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

typedef uint16_t weight_t;

namespace Core
{
  class BoardSeeker
  {
  private:
    Referee *ref;
  private:
    void	prepareTab(std::map<boardPos_t, weight_t> *Tab, boardPos_t pos, weight_t weight);
  public:
    BoardSeeker();
    ~BoardSeeker();
    void	feed(Referee *ref);
    Team	simulate();
    std::map<boardPos_t, weight_t>	getPlayPos();
    std::pair<boardPos_t, weight_t>	getBestPlay();
  };
}

#endif
