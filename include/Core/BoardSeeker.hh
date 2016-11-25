/*
** Alexis Trouvé
*/

#ifndef BOARDSEEKER
#define BOARDSEEKER

#include <vector>
#include <tuple>
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
  public:
    BoardSeeker();
    ~BoardSeeker();
    void	feed(Referee *ref);
    Team	simulate();
    std::vector<std::pair<boardPos_t, weight_t>> getPlayPos();
    std::pair<boardPos_t, weight_t>	getBestPlay();
  };
}

#endif
